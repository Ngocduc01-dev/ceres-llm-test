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
- **Tổng số nhánh** (mẫu số của C2) = 2 × số điểm rẽ nhánh ghi ở dòng đầu CFG (`switch`: mỗi `case` là 1 nhánh). **Không** tính nhánh của `CHECK`.
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `BracketingPhase(const FunctionSample & initial_position, const double step_size_estimate, FunctionSample * bracket_low, FunctionSample * bracket_high, bool * do_zoom_search, Summary * summary) const`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::WolfeLineSearch`
- Vị trí: `internal/ceres/line_search.cc`, dòng 499–692

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
499 | bool WolfeLineSearch::BracketingPhase(const FunctionSample& initial_position,
500 |                                       const double step_size_estimate,
501 |                                       FunctionSample* bracket_low,
502 |                                       FunctionSample* bracket_high,
503 |                                       bool* do_zoom_search,
504 |                                       Summary* summary) const {
505 |   LineSearchFunction* function = options().function;
506 | 
507 |   FunctionSample previous = initial_position;
508 |   FunctionSample current;
509 | 
510 |   const double descent_direction_max_norm = function->DirectionInfinityNorm();
511 | 
512 |   *do_zoom_search = false;
513 |   *bracket_low = initial_position;
514 | 
515 |   // As we require the gradient to evaluate the Wolfe condition, we always
516 |   // calculate it together with the value, irrespective of the interpolation
517 |   // type.  As opposed to only calculating the gradient after the Armijo
518 |   // condition is satisfied, as the computational saving from this approach
519 |   // would be slight (perhaps even negative due to the extra call).  Also,
520 |   // always calculating the value & gradient together protects against us
521 |   // reporting invalid solutions if the cost function returns slightly different
522 |   // function values when evaluated with / without gradients (due to numerical
523 |   // issues).
524 |   ++summary->num_function_evaluations;
525 |   ++summary->num_gradient_evaluations;
526 |   const bool kEvaluateGradient = true;
527 |   function->Evaluate(step_size_estimate, kEvaluateGradient, &current);
528 |   while (true) {
529 |     ++summary->num_iterations;
530 | 
531 |     if (current.value_is_valid &&
532 |         (current.value > (initial_position.value +
533 |                           options().sufficient_decrease *
534 |                               initial_position.gradient * current.x) ||
535 |          (previous.value_is_valid && current.value > previous.value))) {
536 |       // Bracket found: current step size violates Armijo sufficient decrease
537 |       // condition, or has stepped past an inflection point of f() relative to
538 |       // previous step size.
539 |       *do_zoom_search = true;
540 |       *bracket_low = previous;
541 |       *bracket_high = current;
542 |       VLOG(3) << std::scientific
543 |               << std::setprecision(kErrorMessageNumericPrecision)
544 |               << "Bracket found: current step (" << current.x
545 |               << ") violates Armijo sufficient condition, or has passed an "
546 |               << "inflection point of f() based on value.";
547 |       break;
548 |     }
549 | 
550 |     if (current.value_is_valid &&
551 |         fabs(current.gradient) <= -options().sufficient_curvature_decrease *
552 |                                       initial_position.gradient) {
553 |       // Current step size satisfies the strong Wolfe conditions, and is thus a
554 |       // valid termination point, therefore a Zoom not required.
555 |       *bracket_low = current;
556 |       *bracket_high = current;
557 |       VLOG(3) << std::scientific
558 |               << std::setprecision(kErrorMessageNumericPrecision)
559 |               << "Bracketing phase found step size: " << current.x
560 |               << ", satisfying strong Wolfe conditions, initial_position: "
561 |               << initial_position << ", current: " << current;
562 |       break;
563 | 
564 |     } else if (current.value_is_valid && current.gradient >= 0) {
565 |       // Bracket found: current step size has stepped past an inflection point
566 |       // of f(), but Armijo sufficient decrease is still satisfied and
567 |       // f(current) is our best minimum thus far.  Remember step size
568 |       // monotonically increases, thus previous_step_size < current_step_size
569 |       // even though f(previous) > f(current).
570 |       *do_zoom_search = true;
571 |       // Note inverse ordering from first bracket case.
572 |       *bracket_low = current;
573 |       *bracket_high = previous;
574 |       VLOG(3) << "Bracket found: current step (" << current.x
575 |               << ") satisfies Armijo, but has gradient >= 0, thus have passed "
576 |               << "an inflection point of f().";
577 |       break;
578 | 
579 |     } else if (current.value_is_valid &&
580 |                fabs(current.x - previous.x) * descent_direction_max_norm <
581 |                    options().min_step_size) {
582 |       // We have shrunk the search bracket to a width less than our tolerance,
583 |       // and still not found either a point satisfying the strong Wolfe
584 |       // conditions, or a valid bracket containing such a point. Stop searching
585 |       // and set bracket_low to the size size amongst all those tested which
586 |       // minimizes f() and satisfies the Armijo condition.
587 | 
588 |       if (!options().is_silent) {
589 |         LOG(WARNING) << "Line search failed: Wolfe bracketing phase shrank "
590 |                      << "bracket width: " << fabs(current.x - previous.x)
591 |                      << ", to < tolerance: " << options().min_step_size
592 |                      << ", with descent_direction_max_norm: "
593 |                      << descent_direction_max_norm << ", and failed to find "
594 |                      << "a point satisfying the strong Wolfe conditions or a "
595 |                      << "bracketing containing such a point. Accepting "
596 |                      << "point found satisfying Armijo condition only, to "
597 |                      << "allow continuation.";
598 |       }
599 |       *bracket_low = current;
600 |       break;
601 | 
602 |     } else if (summary->num_iterations >= options().max_num_iterations) {
603 |       // Check num iterations bound here so that we always evaluate the
604 |       // max_num_iterations-th iteration against all conditions, and
605 |       // then perform no additional (unused) evaluations.
606 |       summary->error = StringPrintf(
607 |           "Line search failed: Wolfe bracketing phase failed to "
608 |           "find a point satisfying strong Wolfe conditions, or a "
609 |           "bracket containing such a point within specified "
610 |           "max_num_iterations: %d",
611 |           options().max_num_iterations);
612 |       if (!options().is_silent) {
613 |         LOG(WARNING) << summary->error;
614 |       }
615 |       // Ensure that bracket_low is always set to the step size amongst all
616 |       // those tested which minimizes f() and satisfies the Armijo condition
617 |       // when we terminate due to the 'artificial' max_num_iterations condition.
618 |       *bracket_low =
619 |           current.value_is_valid && current.value < bracket_low->value
620 |               ? current
621 |               : *bracket_low;
622 |       break;
623 |     }
624 |     // Either: f(current) is invalid; or, f(current) is valid, but does not
625 |     // satisfy the strong Wolfe conditions itself, or the conditions for
626 |     // being a boundary of a bracket.
627 | 
628 |     // If f(current) is valid, (but meets no criteria) expand the search by
629 |     // increasing the step size.  If f(current) is invalid, contract the step
630 |     // size.
631 |     //
632 |     // In Nocedal & Wright [1] (p60), the step-size can only increase in the
633 |     // bracketing phase: step_size_{k+1} \in [step_size_k, step_size_k *
634 |     // factor]. However this does not account for the function returning invalid
635 |     // values which we support, in which case we need to contract the step size
636 |     // whilst ensuring that we do not invert the bracket, i.e, we require that:
637 |     // step_size_{k-1} <= step_size_{k+1} < step_size_k.
638 |     const double min_step_size =
639 |         current.value_is_valid ? current.x : previous.x;
640 |     const double max_step_size =
641 |         current.value_is_valid ? (current.x * options().max_step_expansion)
642 |                                : current.x;
643 | 
644 |     // We are performing 2-point interpolation only here, but the API of
645 |     // InterpolatingPolynomialMinimizingStepSize() allows for up to
646 |     // 3-point interpolation, so pad call with a sample with an invalid
647 |     // value that will therefore be ignored.
648 |     const FunctionSample unused_previous;
649 |     DCHECK(!unused_previous.value_is_valid);
650 |     // Contracts step size if f(current) is not valid.
651 |     const double polynomial_minimization_start_time = WallTimeInSeconds();
652 |     const double step_size = this->InterpolatingPolynomialMinimizingStepSize(
653 |         options().interpolation_type,
654 |         previous,
655 |         unused_previous,
656 |         current,
657 |         min_step_size,
658 |         max_step_size);
659 |     summary->polynomial_minimization_time_in_seconds +=
660 |         (WallTimeInSeconds() - polynomial_minimization_start_time);
661 |     if (step_size * descent_direction_max_norm < options().min_step_size) {
662 |       summary->error = StringPrintf(
663 |           "Line search failed: step_size too small: %.5e "
664 |           "with descent_direction_max_norm: %.5e",
665 |           step_size,
666 |           descent_direction_max_norm);
667 |       if (!options().is_silent) {
668 |         LOG(WARNING) << summary->error;
669 |       }
670 |       return false;
671 |     }
672 | 
673 |     // Only advance the lower boundary (in x) of the bracket if f(current)
674 |     // is valid such that we can support contracting the step size when
675 |     // f(current) is invalid without risking inverting the bracket in x, i.e.
676 |     // prevent previous.x > current.x.
677 |     previous = current.value_is_valid ? current : previous;
678 |     ++summary->num_function_evaluations;
679 |     ++summary->num_gradient_evaluations;
680 |     function->Evaluate(step_size, kEvaluateGradient, &current);
681 |   }
682 | 
683 |   // Ensure that even if a valid bracket was found, we will only mark a zoom
684 |   // as required if the bracket's width is greater than our minimum tolerance.
685 |   if (*do_zoom_search &&
686 |       fabs(bracket_high->x - bracket_low->x) * descent_direction_max_norm <
687 |           options().min_step_size) {
688 |     *do_zoom_search = false;
689 |   }
690 | 
691 |   return true;
692 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 14 (và 1 lệnh CHECK)

START → 1
1   LineSearchFunction *function = options().function
    const double descent_direction_max_norm = function->DirectionInfinityNorm()
    *do_zoom_search = false
    *bracket_low = initial_position
    ++summary->num_function_evaluations
    ++summary->num_gradient_evaluations
    const bool kEvaluateGradient = true
    function->Evaluate(step_size_estimate, kEvaluateGradient, &current)   → 2
2   while true                                                     → 3
3   ++summary->num_iterations                                      → 4
4   if (current.value_is_valid && (current.value > (initial_position.value + options().sufficient_decrease * initial_position.gradient * current.x) || (previous.value_is_valid && current.value > previous.value)))   đúng → 5   sai → 9
5   *do_zoom_search = true
    *bracket_low = previous
    *bracket_high = current                                        → 6
6   if (*do_zoom_search && fabs(bracket_high->x - bracket_low->x) * descent_direction_max_norm < options().min_step_size)   đúng → 7   sai → 8
7   *do_zoom_search = false                                        → 8
8   return true                                                    → END
9   if (current.value_is_valid && fabs(current.gradient) <= -options().sufficient_curvature_decrease * initial_position.gradient)   đúng → 10   sai → 11
10  *bracket_low = current
    *bracket_high = current                                        → 6
11  if (current.value_is_valid && current.gradient >= 0)           đúng → 12   sai → 13
12  *do_zoom_search = true
    *bracket_low = current
    *bracket_high = previous                                       → 6
13  if (current.value_is_valid && fabs(current.x - previous.x) * descent_direction_max_norm < options().min_step_size)   đúng → 14   sai → 16
14  if (!options().is_silent)                                      đúng → 15   sai → 15
15  *bracket_low = current
    break                                                          → 6
16  if (summary->num_iterations >= options().max_num_iterations)   đúng → 17   sai → 21
17  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->error = StringPrintf("Line search failed: Wolfe bracketing phase failed to find a point satisfying strong Wolfe conditions, or a bracket containing such a point within specified max_num_iterations: %d", options().max_num_iterations)   → 18
18  if (!options().is_silent)                                      đúng → 19   sai → 19
19  current.value_is_valid && current.value < bracket_low->value ? ... : ...   đúng → 20   sai → 20
20  *bracket_low = current.value_is_valid && current.value < bracket_low->value ? current : *bracket_low
    break                                                          → 6
21  current.value_is_valid ? ... : ...                             đúng → 22   sai → 22
22  const double min_step_size = current.value_is_valid ? current.x : previous.x   → 23
23  current.value_is_valid ? ... : ...                             đúng → 24   sai → 24
24  const double max_step_size = current.value_is_valid ? (current.x * options().max_step_expansion) : current.x   → 25
25  DCHECK(!unused_previous.value_is_valid)                        đúng → 26   sai → DỪNG
26  const double polynomial_minimization_start_time = WallTimeInSeconds()
    const double step_size = InterpolatingPolynomialMinimizingStepSize(options().interpolation_type, previous, unused_previous, current, min_step_size, max_step_size)
    summary->polynomial_minimization_time_in_seconds += (WallTimeInSeconds() - polynomial_minimization_start_time)   → 27
27  if (step_size * descent_direction_max_norm < options().min_step_size)   đúng → 28   sai → 31
28  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->error = StringPrintf("Line search failed: step_size too small: %.5e with descent_direction_max_norm: %.5e", step_size, descent_direction_max_norm)   → 29
29  if (!options().is_silent)                                      đúng → 30   sai → 30
30  return false                                                   → END
31  current.value_is_valid ? ... : ...                             đúng → 32   sai → 32
32  previous = current.value_is_valid ? current : previous
    ++summary->num_function_evaluations
    ++summary->num_gradient_evaluations
    function->Evaluate(step_size, kEvaluateGradient, &current)     → 2
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1505_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
