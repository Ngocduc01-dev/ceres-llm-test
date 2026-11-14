# 1. NHIỆM VỤ

Bạn là kỹ sư kiểm thử phần mềm. Hãy thiết kế bộ test cho **một hàm C++** (gọi là **unit**) ở mục 3 theo phương pháp **kiểm thử luồng điều khiển (CFT)**, sao cho đạt **độ phủ nhánh C2**, rồi viết bộ test đó thành **một file GoogleTest** (thư viện viết unit test cho C++) chạy được.

- Dự án: thư viện **Ceres Solver 2.2.0**, viết bằng C++17.
- Dự án **không có tài liệu mô tả kết quả đúng**, nên **không cần kiểm tra kết quả trả về**. Mục tiêu chỉ là gọi hàm sao cho chương trình **đi qua đủ các nhánh**.

---

# 2. KHÁI NIỆM CẦN DÙNG

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

- Hàm: `Solve(const Solver::Options & options, Problem * problem, Solver::Summary * summary)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::Solver`
- Vị trí: `internal/ceres/solver.cc`, dòng 710–830

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
710 | void Solver::Solve(const Solver::Options& options,
711 |                    Problem* problem,
712 |                    Solver::Summary* summary) {
713 |   using internal::PreprocessedProblem;
714 |   using internal::Preprocessor;
715 |   using internal::ProblemImpl;
716 |   using internal::Program;
717 |   using internal::WallTimeInSeconds;
718 | 
719 |   CHECK(problem != nullptr);
720 |   CHECK(summary != nullptr);
721 | 
722 |   double start_time = WallTimeInSeconds();
723 |   *summary = Summary();
724 |   if (!options.IsValid(&summary->message)) {
725 |     LOG(ERROR) << "Terminating: " << summary->message;
726 |     return;
727 |   }
728 | 
729 |   ProblemImpl* problem_impl = problem->mutable_impl();
730 |   Program* program = problem_impl->mutable_program();
731 |   PreSolveSummarize(options, problem_impl, summary);
732 | 
733 | #ifndef CERES_NO_CUDA
734 |   if (IsCudaRequired(options)) {
735 |     if (!problem_impl->context()->InitCuda(&summary->message)) {
736 |       LOG(ERROR) << "Terminating: " << summary->message;
737 |       return;
738 |     }
739 |   }
740 | #endif  // CERES_NO_CUDA
741 | 
742 |   // If gradient_checking is enabled, wrap all cost functions in a
743 |   // gradient checker and install a callback that terminates if any gradient
744 |   // error is detected.
745 |   std::unique_ptr<internal::ProblemImpl> gradient_checking_problem;
746 |   internal::GradientCheckingIterationCallback gradient_checking_callback;
747 |   Solver::Options modified_options = options;
748 |   if (options.check_gradients) {
749 |     modified_options.callbacks.push_back(&gradient_checking_callback);
750 |     gradient_checking_problem = CreateGradientCheckingProblemImpl(
751 |         problem_impl,
752 |         options.gradient_check_numeric_derivative_relative_step_size,
753 |         options.gradient_check_relative_precision,
754 |         &gradient_checking_callback);
755 |     problem_impl = gradient_checking_problem.get();
756 |     program = problem_impl->mutable_program();
757 |   }
758 | 
759 |   // Make sure that all the parameter blocks states are set to the
760 |   // values provided by the user.
761 |   program->SetParameterBlockStatePtrsToUserStatePtrs();
762 | 
763 |   // The main thread also does work so we only need to launch num_threads - 1.
764 |   problem_impl->context()->EnsureMinimumThreads(options.num_threads - 1);
765 | 
766 |   auto preprocessor = Preprocessor::Create(modified_options.minimizer_type);
767 |   PreprocessedProblem pp;
768 | 
769 |   const bool status =
770 |       preprocessor->Preprocess(modified_options, problem_impl, &pp);
771 | 
772 |   // We check the linear_solver_options.type rather than
773 |   // modified_options.linear_solver_type because, depending on the
774 |   // lack of a Schur structure, the preprocessor may change the linear
775 |   // solver type.
776 |   if (IsSchurType(pp.linear_solver_options.type)) {
777 |     // TODO(sameeragarwal): We can likely eliminate the duplicate call
778 |     // to DetectStructure here and inside the linear solver, by
779 |     // calling this in the preprocessor.
780 |     int row_block_size;
781 |     int e_block_size;
782 |     int f_block_size;
783 |     DetectStructure(*static_cast<internal::BlockSparseMatrix*>(
784 |                          pp.minimizer_options.jacobian.get())
785 |                          ->block_structure(),
786 |                     pp.linear_solver_options.elimination_groups[0],
787 |                     &row_block_size,
788 |                     &e_block_size,
789 |                     &f_block_size);
790 |     summary->schur_structure_given =
791 |         SchurStructureToString(row_block_size, e_block_size, f_block_size);
792 |     internal::GetBestSchurTemplateSpecialization(
793 |         &row_block_size, &e_block_size, &f_block_size);
794 |     summary->schur_structure_used =
795 |         SchurStructureToString(row_block_size, e_block_size, f_block_size);
796 |   }
797 | 
798 |   summary->fixed_cost = pp.fixed_cost;
799 |   summary->preprocessor_time_in_seconds = WallTimeInSeconds() - start_time;
800 | 
801 |   if (status) {
802 |     const double minimizer_start_time = WallTimeInSeconds();
803 |     Minimize(&pp, summary);
804 |     summary->minimizer_time_in_seconds =
805 |         WallTimeInSeconds() - minimizer_start_time;
806 |   } else {
807 |     summary->message = pp.error;
808 |   }
809 | 
810 |   const double postprocessor_start_time = WallTimeInSeconds();
811 |   problem_impl = problem->mutable_impl();
812 |   program = problem_impl->mutable_program();
813 |   // On exit, ensure that the parameter blocks again point at the user
814 |   // provided values and the parameter blocks are numbered according
815 |   // to their position in the original user provided program.
816 |   program->SetParameterBlockStatePtrsToUserStatePtrs();
817 |   program->SetParameterOffsetsAndIndex();
818 |   PostSolveSummarize(pp, summary);
819 |   summary->postprocessor_time_in_seconds =
820 |       WallTimeInSeconds() - postprocessor_start_time;
821 | 
822 |   // If the gradient checker reported an error, we want to report FAILURE
823 |   // instead of USER_FAILURE and provide the error log.
824 |   if (gradient_checking_callback.gradient_error_detected()) {
825 |     summary->termination_type = FAILURE;
826 |     summary->message = gradient_checking_callback.error_log();
827 |   }
828 | 
829 |   summary->total_time_in_seconds = WallTimeInSeconds() - start_time;
830 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 5 (và 2 lệnh CHECK)

START → 1
1   CHECK(problem != nullptr)                                      đúng → 2   sai → DỪNG
2   CHECK(summary != nullptr)                                      đúng → 3   sai → DỪNG
3   double start_time = WallTimeInSeconds()
    *summary = Summary()                                           → 4
4   if (!options.IsValid(&summary->message))                       đúng → END   sai → 5
5   ProblemImpl *problem_impl = problem->mutable_impl()
    Program *program = problem_impl->mutable_program()
    PreSolveSummarize(options, problem_impl, summary)              → 6
6   if (options.check_gradients)                                   đúng → 7   sai → 8
7   modified_options.callbacks.push_back(&gradient_checking_callback)
    gradient_checking_problem = CreateGradientCheckingProblemImpl(problem_impl, options.gradient_check_numeric_derivative_relative_step_size, options.gradient_check_relative_precision, &gradient_checking_callback)
    problem_impl = gradient_checking_problem.get()
    program = problem_impl->mutable_program()                      → 8
8   program->SetParameterBlockStatePtrsToUserStatePtrs()
    problem_impl->context()->EnsureMinimumThreads(options.num_threads - 1)
    const bool status = preprocessor->Preprocess(modified_options, problem_impl, &pp)   → 9
9   if (IsSchurType(pp.linear_solver_options.type))                đúng → 10   sai → 11
10  int row_block_size
    int e_block_size
    int f_block_size
    DetectStructure(*static_cast<internal::BlockSparseMatrix *>(pp.minimizer_options.jacobian.get())->block_structure(), pp.linear_solver_options.elimination_groups[0], &row_block_size, &e_block_size, &f_block_size)
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->schur_structure_given = SchurStructureToString(row_block_size, e_block_size, f_block_size)
    internal::GetBestSchurTemplateSpecialization(&row_block_size, &e_block_size, &f_block_size)
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->schur_structure_used = SchurStructureToString(row_block_size, e_block_size, f_block_size)   → 11
11  summary->fixed_cost = pp.fixed_cost
    summary->preprocessor_time_in_seconds = WallTimeInSeconds() - start_time   → 12
12  if (status)                                                    đúng → 13   sai → 18
13  const double minimizer_start_time = WallTimeInSeconds()
    Minimize(&pp, summary)
    summary->minimizer_time_in_seconds = WallTimeInSeconds() - minimizer_start_time   → 14
14  const double postprocessor_start_time = WallTimeInSeconds()
    problem_impl = problem->mutable_impl()
    program = problem_impl->mutable_program()
    program->SetParameterBlockStatePtrsToUserStatePtrs()
    program->SetParameterOffsetsAndIndex()
    PostSolveSummarize(pp, summary)
    summary->postprocessor_time_in_seconds = WallTimeInSeconds() - postprocessor_start_time   → 15
15  if (gradient_checking_callback.gradient_error_detected())      đúng → 16   sai → 17
16  summary->termination_type = FAILURE
    summary->message = gradient_checking_callback.error_log()      → 17
17  summary->total_time_in_seconds = WallTimeInSeconds() - start_time   → END
18  summary->message = pp.error                                    → 14
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
#include "ceres/problem.h"
#include "ceres/solver.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/gradient_checking_cost_function.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
```

- Đây là method của class `ceres::Solver`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `Solver`:
Các constructor:
```cpp
  Solver()
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1533_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
