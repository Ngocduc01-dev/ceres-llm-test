# 1. NHIỆM VỤ

Bạn là kỹ sư kiểm thử phần mềm. Hãy thiết kế bộ test cho **một hàm C++** (gọi là **unit**) ở mục 3 theo phương pháp **kiểm thử luồng điều khiển (CFT)**, sao cho đạt **độ phủ nhánh C2**, rồi viết bộ test đó thành **một file GoogleTest** (thư viện viết unit test cho C++) chạy được.

- Dự án: thư viện **Ceres Solver 2.2.0**, viết bằng C++17.
- Dự án **không có tài liệu mô tả kết quả đúng**, nên **không cần kiểm tra kết quả trả về**. Mục tiêu chỉ là gọi hàm sao cho chương trình **đi qua đủ các nhánh**.

---

# 2. KHÁI NIỆM

- **CFG (đồ thị luồng điều khiển):** sơ đồ các bước của hàm. Mỗi **node** là một đoạn lệnh chạy liền nhau hoặc một chỗ rẽ nhánh; mũi tên nối các node theo thứ tự chạy.
- **Điểm rẽ nhánh:** chỗ chương trình chọn đường đi theo một điều kiện: `if`, `else if`, vòng `for` / `while`, `switch`, `?:`. Mỗi điểm rẽ nhánh có **2 nhánh**: điều kiện **đúng** và điều kiện **sai** (`switch` có 1 nhánh cho mỗi `case`).
- **Độ phủ C2 (phủ nhánh):** mọi nhánh của mọi điểm rẽ nhánh đều được chạy qua ít nhất 1 lần.
  **C2 = số nhánh đã chạy qua / tổng số nhánh × 100%.**
  (C2 chặt hơn C1 – chỉ yêu cầu mỗi câu lệnh chạy ít nhất 1 lần. Ví dụ `if (x > 0) y = 1;`: chỉ cần x > 0 là đạt C1, nhưng C2 cần thêm 1 test với x ≤ 0.)
  Điều kiện ghép như `a && b`, `a || b` được tính là **một** điểm rẽ nhánh.
- **Test path (đường kiểm thử):** một đường đi trên CFG, từ `START` tới `END`, ghi rõ ở mỗi điểm rẽ nhánh đi theo nhánh nào.
- **Điều kiện của đường đi:** các điều kiện phải đúng/sai dọc theo một test path. Dữ liệu đầu vào của test phải thoả các điều kiện này.
- **Nhánh không thể đi tới:** nhánh mà không có dữ liệu nào làm chương trình đi vào (ví dụ điều kiện mâu thuẫn). Ghi rõ lý do, vẫn tính vào tổng số nhánh.
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `ZoomPhase(const FunctionSample & initial_position, FunctionSample bracket_low, FunctionSample bracket_high, FunctionSample * solution, Summary * summary) const`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::WolfeLineSearch`
- Vị trí: `internal/ceres/line_search.cc`, dòng 698–881

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
698 | bool WolfeLineSearch::ZoomPhase(const FunctionSample& initial_position,
699 |                                 FunctionSample bracket_low,
700 |                                 FunctionSample bracket_high,
701 |                                 FunctionSample* solution,
702 |                                 Summary* summary) const {
703 |   LineSearchFunction* function = options().function;
704 | 
705 |   CHECK(bracket_low.value_is_valid && bracket_low.gradient_is_valid)
706 |       << std::scientific << std::setprecision(kErrorMessageNumericPrecision)
707 |       << "Ceres bug: f_low input to Wolfe Zoom invalid, please contact "
708 |       << "the developers!, initial_position: " << initial_position
709 |       << ", bracket_low: " << bracket_low << ", bracket_high: " << bracket_high;
710 |   // We do not require bracket_high.gradient_is_valid as the gradient condition
711 |   // for a valid bracket is only dependent upon bracket_low.gradient, and
712 |   // in order to minimize jacobian evaluations, bracket_high.gradient may
713 |   // not have been calculated (if bracket_high.value does not satisfy the
714 |   // Armijo sufficient decrease condition and interpolation method does not
715 |   // require it).
716 |   //
717 |   // We also do not require that: bracket_low.value < bracket_high.value,
718 |   // although this is typical. This is to deal with the case when
719 |   // bracket_low = initial_position, bracket_high is the first sample,
720 |   // and bracket_high does not satisfy the Armijo condition, but still has
721 |   // bracket_high.value < initial_position.value.
722 |   CHECK(bracket_high.value_is_valid)
723 |       << std::scientific << std::setprecision(kErrorMessageNumericPrecision)
724 |       << "Ceres bug: f_high input to Wolfe Zoom invalid, please "
725 |       << "contact the developers!, initial_position: " << initial_position
726 |       << ", bracket_low: " << bracket_low << ", bracket_high: " << bracket_high;
727 | 
728 |   if (bracket_low.gradient * (bracket_high.x - bracket_low.x) >= 0) {
729 |     // The third condition for a valid initial bracket:
730 |     //
731 |     //   3. bracket_high is chosen after bracket_low, s.t.
732 |     //      bracket_low.gradient * (bracket_high.x - bracket_low.x) < 0.
733 |     //
734 |     // is not satisfied.  As this can happen when the users' cost function
735 |     // returns inconsistent gradient values relative to the function values,
736 |     // we do not CHECK_LT(), but we do stop processing and return an invalid
737 |     // value.
738 |     summary->error = StringPrintf(
739 |         "Line search failed: Wolfe zoom phase passed a bracket "
740 |         "which does not satisfy: bracket_low.gradient * "
741 |         "(bracket_high.x - bracket_low.x) < 0 [%.8e !< 0] "
742 |         "with initial_position: %s, bracket_low: %s, bracket_high:"
743 |         " %s, the most likely cause of which is the cost function "
744 |         "returning inconsistent gradient & function values.",
745 |         bracket_low.gradient * (bracket_high.x - bracket_low.x),
746 |         initial_position.ToDebugString().c_str(),
747 |         bracket_low.ToDebugString().c_str(),
748 |         bracket_high.ToDebugString().c_str());
749 |     if (!options().is_silent) {
750 |       LOG(WARNING) << summary->error;
751 |     }
752 |     solution->value_is_valid = false;
753 |     return false;
754 |   }
755 | 
756 |   const int num_bracketing_iterations = summary->num_iterations;
757 |   const double descent_direction_max_norm = function->DirectionInfinityNorm();
758 | 
759 |   while (true) {
760 |     // Set solution to bracket_low, as it is our best step size (smallest f())
761 |     // found thus far and satisfies the Armijo condition, even though it does
762 |     // not satisfy the Wolfe condition.
763 |     *solution = bracket_low;
764 |     if (summary->num_iterations >= options().max_num_iterations) {
765 |       summary->error = StringPrintf(
766 |           "Line search failed: Wolfe zoom phase failed to "
767 |           "find a point satisfying strong Wolfe conditions "
768 |           "within specified max_num_iterations: %d, "
769 |           "(num iterations taken for bracketing: %d).",
770 |           options().max_num_iterations,
771 |           num_bracketing_iterations);
772 |       if (!options().is_silent) {
773 |         LOG(WARNING) << summary->error;
774 |       }
775 |       return false;
776 |     }
777 |     if (fabs(bracket_high.x - bracket_low.x) * descent_direction_max_norm <
778 |         options().min_step_size) {
779 |       // Bracket width has been reduced below tolerance, and no point satisfying
780 |       // the strong Wolfe conditions has been found.
781 |       summary->error = StringPrintf(
782 |           "Line search failed: Wolfe zoom bracket width: %.5e "
783 |           "too small with descent_direction_max_norm: %.5e.",
784 |           fabs(bracket_high.x - bracket_low.x),
785 |           descent_direction_max_norm);
786 |       if (!options().is_silent) {
787 |         LOG(WARNING) << summary->error;
788 |       }
789 |       return false;
790 |     }
791 | 
792 |     ++summary->num_iterations;
793 |     // Polynomial interpolation requires inputs ordered according to step size,
794 |     // not f(step size).
795 |     const FunctionSample& lower_bound_step =
796 |         bracket_low.x < bracket_high.x ? bracket_low : bracket_high;
797 |     const FunctionSample& upper_bound_step =
798 |         bracket_low.x < bracket_high.x ? bracket_high : bracket_low;
799 |     // We are performing 2-point interpolation only here, but the API of
800 |     // InterpolatingPolynomialMinimizingStepSize() allows for up to
801 |     // 3-point interpolation, so pad call with a sample with an invalid
802 |     // value that will therefore be ignored.
803 |     const FunctionSample unused_previous;
804 |     DCHECK(!unused_previous.value_is_valid);
805 |     const double polynomial_minimization_start_time = WallTimeInSeconds();
806 |     const double step_size = this->InterpolatingPolynomialMinimizingStepSize(
807 |         options().interpolation_type,
808 |         lower_bound_step,
809 |         unused_previous,
810 |         upper_bound_step,
811 |         lower_bound_step.x,
812 |         upper_bound_step.x);
813 |     summary->polynomial_minimization_time_in_seconds +=
814 |         (WallTimeInSeconds() - polynomial_minimization_start_time);
815 |     // No check on magnitude of step size being too small here as it is
816 |     // lower-bounded by the initial bracket start point, which was valid.
817 |     //
818 |     // As we require the gradient to evaluate the Wolfe condition, we always
819 |     // calculate it together with the value, irrespective of the interpolation
820 |     // type.  As opposed to only calculating the gradient after the Armijo
821 |     // condition is satisfied, as the computational saving from this approach
822 |     // would be slight (perhaps even negative due to the extra call).  Also,
823 |     // always calculating the value & gradient together protects against us
824 |     // reporting invalid solutions if the cost function returns slightly
825 |     // different function values when evaluated with / without gradients (due
826 |     // to numerical issues).
827 |     ++summary->num_function_evaluations;
828 |     ++summary->num_gradient_evaluations;
829 |     const bool kEvaluateGradient = true;
830 |     function->Evaluate(step_size, kEvaluateGradient, solution);
831 |     if (!solution->value_is_valid || !solution->gradient_is_valid) {
832 |       summary->error = StringPrintf(
833 |           "Line search failed: Wolfe Zoom phase found "
834 |           "step_size: %.5e, for which function is invalid, "
835 |           "between low_step: %.5e and high_step: %.5e "
836 |           "at which function is valid.",
837 |           solution->x,
838 |           bracket_low.x,
839 |           bracket_high.x);
840 |       if (!options().is_silent) {
841 |         LOG(WARNING) << summary->error;
842 |       }
843 |       return false;
844 |     }
845 | 
846 |     VLOG(3) << "Zoom iteration: "
847 |             << summary->num_iterations - num_bracketing_iterations
848 |             << ", bracket_low: " << bracket_low
849 |             << ", bracket_high: " << bracket_high
850 |             << ", minimizing solution: " << *solution;
851 | 
852 |     if ((solution->value > (initial_position.value +
853 |                             options().sufficient_decrease *
854 |                                 initial_position.gradient * solution->x)) ||
855 |         (solution->value >= bracket_low.value)) {
856 |       // Armijo sufficient decrease not satisfied, or not better
857 |       // than current lowest sample, use as new upper bound.
858 |       bracket_high = *solution;
859 |       continue;
860 |     }
861 | 
862 |     // Armijo sufficient decrease satisfied, check strong Wolfe condition.
863 |     if (fabs(solution->gradient) <=
864 |         -options().sufficient_curvature_decrease * initial_position.gradient) {
865 |       // Found a valid termination point satisfying strong Wolfe conditions.
866 |       VLOG(3) << std::scientific
867 |               << std::setprecision(kErrorMessageNumericPrecision)
868 |               << "Zoom phase found step size: " << solution->x
869 |               << ", satisfying strong Wolfe conditions.";
870 |       break;
871 | 
872 |     } else if (solution->gradient * (bracket_high.x - bracket_low.x) >= 0) {
873 |       bracket_high = bracket_low;
874 |     }
875 | 
876 |     bracket_low = *solution;
877 |   }
878 |   // Solution contains a valid point which satisfies the strong Wolfe
879 |   // conditions.
880 |   return true;
881 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 13 (và 3 lệnh CHECK)

START → 1
1   LineSearchFunction *function = options().function              → 2
2   CHECK(bracket_low.value_is_valid && bracket_low.gradient_is_valid)   đúng → 3   sai → DỪNG
3   CHECK(bracket_high.value_is_valid)                             đúng → 4   sai → DỪNG
4   if (bracket_low.gradient * (bracket_high.x - bracket_low.x) >= 0)   đúng → 5   sai → 8
5   operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->error = StringPrintf("Line search failed: Wolfe zoom phase passed a bracket which does not satisfy: bracket_low.gradient * (bracket_high.x - bracket_low.x) < 0 [%.8e !< 0] with initial_position: %s, bracket_low: %s, bracket_high: %s, the most likely cause of which is the cost function returning inconsistent gradient & function values.", bracket_low.gradient * (bracket_high.x - bracket_low.x), initial_position.ToDebugString().c_str(), bracket_low.ToDebugString().c_str(), bracket_high.ToDebugString().c_str())   → 6
6   if (!options().is_silent)                                      đúng → 7   sai → 7
7   solution->value_is_valid = false
    return false                                                   → END
8   const int num_bracketing_iterations = summary->num_iterations
    const double descent_direction_max_norm = function->DirectionInfinityNorm()   → 9
9   while true                                                     → 10
10  *solution = bracket_low                                        → 11
11  if (summary->num_iterations >= options().max_num_iterations)   đúng → 12   sai → 15
12  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->error = StringPrintf("Line search failed: Wolfe zoom phase failed to find a point satisfying strong Wolfe conditions within specified max_num_iterations: %d, (num iterations taken for bracketing: %d).", options().max_num_iterations, num_bracketing_iterations)   → 13
13  if (!options().is_silent)                                      đúng → 14   sai → 14
14  return false                                                   → END
15  if (fabs(bracket_high.x - bracket_low.x) * descent_direction_max_norm < options().min_step_size)   đúng → 16   sai → 19
16  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->error = StringPrintf("Line search failed: Wolfe zoom bracket width: %.5e too small with descent_direction_max_norm: %.5e.", fabs(bracket_high.x - bracket_low.x), descent_direction_max_norm)   → 17
17  if (!options().is_silent)                                      đúng → 18   sai → 18
18  return false                                                   → END
19  ++summary->num_iterations                                      → 20
20  bracket_low.x < bracket_high.x ? ... : ...                     đúng → 21   sai → 21
21  const FunctionSample &lower_bound_step = bracket_low.x < bracket_high.x ? bracket_low : bracket_high   → 22
22  bracket_low.x < bracket_high.x ? ... : ...                     đúng → 23   sai → 23
23  const FunctionSample &upper_bound_step = bracket_low.x < bracket_high.x ? bracket_high : bracket_low   → 24
24  DCHECK(!unused_previous.value_is_valid)                        đúng → 25   sai → DỪNG
25  const double polynomial_minimization_start_time = WallTimeInSeconds()
    const double step_size = InterpolatingPolynomialMinimizingStepSize(options().interpolation_type, lower_bound_step, unused_previous, upper_bound_step, lower_bound_step.x, upper_bound_step.x)
    summary->polynomial_minimization_time_in_seconds += (WallTimeInSeconds() - polynomial_minimization_start_time)
    ++summary->num_function_evaluations
    ++summary->num_gradient_evaluations
    const bool kEvaluateGradient = true
    function->Evaluate(step_size, kEvaluateGradient, solution)     → 26
26  if (!solution->value_is_valid || !solution->gradient_is_valid)   đúng → 27   sai → 30
27  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->error = StringPrintf("Line search failed: Wolfe Zoom phase found step_size: %.5e, for which function is invalid, between low_step: %.5e and high_step: %.5e at which function is valid.", solution->x, bracket_low.x, bracket_high.x)   → 28
28  if (!options().is_silent)                                      đúng → 29   sai → 29
29  return false                                                   → END
30  if (solution->value > (initial_position.value + options().sufficient_decrease * initial_position.gradient * solution->x)) || (solution->value >= bracket_low.value)   đúng → 31   sai → 32
31  bracket_high = *solution
    continue                                                       → 9
32  if (fabs(solution->gradient) <= -options().sufficient_curvature_decrease * initial_position.gradient)   đúng → 33   sai → 34
33  return true                                                    → END
34  if (solution->gradient * (bracket_high.x - bracket_low.x) >= 0)   đúng → 35   sai → 36
35  bracket_high = bracket_low                                     → 36
36  bracket_low = *solution                                        → 9
```

**Cách đọc:** dòng đầu cho biết hàm có bao nhiêu điểm rẽ nhánh. Mỗi dòng sau đó là **một node**: số node, nội dung (câu lệnh hoặc điều kiện), rồi mũi tên tới node tiếp theo. Dòng "Ghi chú" (nếu có) cho biết unit là template và CFG được dựng với kiểu dữ liệu cụ thể nào.
- Node có điều kiện ghi `đúng → x   sai → y`: điều kiện đúng thì đi tới node x, sai thì đi tới node y.
- `START`: bắt đầu hàm · `END`: kết thúc hàm · `DỪNG`: chương trình dừng do `CHECK` sai.
- Nếu thấy CFG không khớp với mã nguồn, **tin mã nguồn** và ghi chú lại.
- Khi trả lời, gọi các node bằng **đúng số node này**.

## 3.3. Cách gọi unit trong file test

Các dòng `#include` được dùng:
```cpp
#include "gtest/gtest.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"
```

- Đây là method của class `ceres::internal::WolfeLineSearch`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `WolfeLineSearch`:
Các constructor:
```cpp
  WolfeLineSearch(const LineSearch::Options & options)
```

---

# 4. YÊU CẦU ĐỐI VỚI BỘ TEST

1. Mỗi nhánh (đúng và sai) của mỗi điểm rẽ nhánh có **ít nhất 1 test** đi qua.
2. Mỗi vòng lặp được test với số lần lặp như mục 2.
3. Mỗi test ứng với **một test path**, ghi rõ các nhánh nó đi qua (ví dụ `node 2: đúng, node 4: sai`).
4. Dùng **ít test nhất** có thể: một test nên đi qua nhiều nhánh chưa được phủ.
5. **Dữ liệu đầu vào:** từ điều kiện của đường đi, xác định **khoảng giá trị** hợp lệ cho từng đầu vào (ví dụ `n` từ 1 đến 5), rồi **chọn ngẫu nhiên một giá trị** trong khoảng đó. Nếu dùng hàm sinh số ngẫu nhiên trong code thì **cố định giá trị khởi tạo (seed)** để mỗi lần chạy ra cùng một giá trị. Mảng, ma trận nhỏ (tối đa 5 phần tử). Không dùng file, mạng, đa luồng.
6. **Không** kiểm tra kết quả trả về (không có kết quả đúng để so).

---

# 5. CÁC BƯỚC THỰC HIỆN

1. Đọc mã nguồn và CFG của unit.
2. Liệt kê các điểm rẽ nhánh và các nhánh cần phủ.
3. Chọn các test path sao cho phủ hết các nhánh (trừ nhánh không thể đi tới và nhánh `CHECK` sai).
4. Với mỗi test path: viết điều kiện của đường đi → khoảng giá trị đầu vào → chọn giá trị ngẫu nhiên trong khoảng.
5. Viết code GoogleTest: mỗi test chuẩn bị dữ liệu rồi gọi unit **một lần**.
6. Kiểm tra lại: mọi nhánh đã có test chưa, code có dùng đúng tên hàm và `#include` ở mục 3.3 không.

---

# 6. KẾT QUẢ CẦN TRẢ VỀ

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → … → END | node 1: đúng, node 2: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | … | … |

**C. Nhánh không test** (nếu có): nhánh nào, vì sao. Kèm 1 dòng: `C2 dự kiến = <số nhánh có test> / <tổng số nhánh>` (dự kiến, chưa chạy thật).

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1504_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
