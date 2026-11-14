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

- Hàm: `ComputeGaussNewtonStep(const PerSolveOptions & per_solve_options, SparseMatrix * jacobian, const double * residuals)`, trả về `LinearSolver::Summary`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::DoglegStrategy`
- Vị trí: `internal/ceres/dogleg_strategy.cc`, dòng 516–615

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
516 | LinearSolver::Summary DoglegStrategy::ComputeGaussNewtonStep(
517 |     const PerSolveOptions& per_solve_options,
518 |     SparseMatrix* jacobian,
519 |     const double* residuals) {
520 |   const int n = jacobian->num_cols();
521 |   LinearSolver::Summary linear_solver_summary;
522 |   linear_solver_summary.termination_type = LinearSolverTerminationType::FAILURE;
523 | 
524 |   // The Jacobian matrix is often quite poorly conditioned. Thus it is
525 |   // necessary to add a diagonal matrix at the bottom to prevent the
526 |   // linear solver from failing.
527 |   //
528 |   // We do this by computing the same diagonal matrix as the one used
529 |   // by Levenberg-Marquardt (other choices are possible), and scaling
530 |   // it by a small constant (independent of the trust region radius).
531 |   //
532 |   // If the solve fails, the multiplier to the diagonal is increased
533 |   // up to max_mu_ by a factor of mu_increase_factor_ every time. If
534 |   // the linear solver is still not successful, the strategy returns
535 |   // with LinearSolverTerminationType::FAILURE.
536 |   //
537 |   // Next time when a new Gauss-Newton step is requested, the
538 |   // multiplier starts out from the last successful solve.
539 |   //
540 |   // When a step is declared successful, the multiplier is decreased
541 |   // by half of mu_increase_factor_.
542 | 
543 |   while (mu_ < max_mu_) {
544 |     // Dogleg, as far as I (sameeragarwal) understand it, requires a
545 |     // reasonably good estimate of the Gauss-Newton step. This means
546 |     // that we need to solve the normal equations more or less
547 |     // exactly. This is reflected in the values of the tolerances set
548 |     // below.
549 |     //
550 |     // For now, this strategy should only be used with exact
551 |     // factorization based solvers, for which these tolerances are
552 |     // automatically satisfied.
553 |     //
554 |     // The right way to combine inexact solves with trust region
555 |     // methods is to use Stiehaug's method.
556 |     LinearSolver::PerSolveOptions solve_options;
557 |     solve_options.q_tolerance = 0.0;
558 |     solve_options.r_tolerance = 0.0;
559 | 
560 |     lm_diagonal_ = diagonal_ * std::sqrt(mu_);
561 |     solve_options.D = lm_diagonal_.data();
562 | 
563 |     // As in the LevenbergMarquardtStrategy, solve Jy = r instead
564 |     // of Jx = -r and later set x = -y to avoid having to modify
565 |     // either jacobian or residuals.
566 |     InvalidateArray(n, gauss_newton_step_.data());
567 |     linear_solver_summary = linear_solver_->Solve(
568 |         jacobian, residuals, solve_options, gauss_newton_step_.data());
569 | 
570 |     if (per_solve_options.dump_format_type == CONSOLE ||
571 |         (per_solve_options.dump_format_type != CONSOLE &&
572 |          !per_solve_options.dump_filename_base.empty())) {
573 |       if (!DumpLinearLeastSquaresProblem(per_solve_options.dump_filename_base,
574 |                                          per_solve_options.dump_format_type,
575 |                                          jacobian,
576 |                                          solve_options.D,
577 |                                          residuals,
578 |                                          gauss_newton_step_.data(),
579 |                                          0)) {
580 |         LOG(ERROR) << "Unable to dump trust region problem."
581 |                    << " Filename base: "
582 |                    << per_solve_options.dump_filename_base;
583 |       }
584 |     }
585 | 
586 |     if (linear_solver_summary.termination_type ==
587 |         LinearSolverTerminationType::FATAL_ERROR) {
588 |       return linear_solver_summary;
589 |     }
590 | 
591 |     if (linear_solver_summary.termination_type ==
592 |             LinearSolverTerminationType::FAILURE ||
593 |         !IsArrayValid(n, gauss_newton_step_.data())) {
594 |       mu_ *= mu_increase_factor_;
595 |       VLOG(2) << "Increasing mu " << mu_;
596 |       linear_solver_summary.termination_type =
597 |           LinearSolverTerminationType::FAILURE;
598 |       continue;
599 |     }
600 |     break;
601 |   }
602 | 
603 |   if (linear_solver_summary.termination_type !=
604 |       LinearSolverTerminationType::FAILURE) {
605 |     // The scaled Gauss-Newton step is D * GN:
606 |     //
607 |     //     - (D^-1 J^T J D^-1)^-1 (D^-1 g)
608 |     //   = - D (J^T J)^-1 D D^-1 g
609 |     //   = D -(J^T J)^-1 g
610 |     //
611 |     gauss_newton_step_.array() *= -diagonal_.array();
612 |   }
613 | 
614 |   return linear_solver_summary;
615 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 6

START → 1
1   const int n = jacobian->num_cols()
    linear_solver_summary.termination_type = LinearSolverTerminationType::FAILURE   → 2
2   while (mu_ < max_mu_)                                          đúng → 3   sai → 10
3   solve_options.q_tolerance = 0.
    solve_options.r_tolerance = 0.
    lm_diagonal_ = diagonal_ * std::sqrt(mu_)
    solve_options.D = lm_diagonal_.data()
    InvalidateArray(n, gauss_newton_step_.data())
    linear_solver_summary = linear_solver_->Solve(jacobian, residuals, solve_options, gauss_newton_step_.data())   → 4
4   if (per_solve_options.dump_format_type == CONSOLE || (per_solve_options.dump_format_type != CONSOLE && !per_solve_options.dump_filename_base.empty()))   đúng → 5   sai → 6
5   if (!DumpLinearLeastSquaresProblem(per_solve_options.dump_filename_base, per_solve_options.dump_format_type, jacobian, solve_options.D, residuals, gauss_newton_step_.data(), 0))   đúng → 6   sai → 6
6   if (linear_solver_summary.termination_type == LinearSolverTerminationType::FATAL_ERROR)   đúng → END   sai → 7
7   if (linear_solver_summary.termination_type == LinearSolverTerminationType::FAILURE || !IsArrayValid(n, gauss_newton_step_.data()))   đúng → 8   sai → 9
8   mu_ *= mu_increase_factor_                                     → 2
9   break                                                          → 10
10  if (linear_solver_summary.termination_type != LinearSolverTerminationType::FAILURE)   đúng → 11   sai → END
11  gauss_newton_step_.array() *= - diagonal_.array()              → END
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
#include "ceres/dogleg_strategy.h"
#include "ceres/linear_solver.h"
#include "ceres/sparse_matrix.h"
#include "ceres/trust_region_strategy.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::DoglegStrategy`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `DoglegStrategy`:
Các constructor:
```cpp
  DoglegStrategy(const TrustRegionStrategy::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1497_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
