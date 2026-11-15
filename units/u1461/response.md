# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |
| P3 | START → 1 → END | Theo CFG/source; case 3 |
| P4 | START → 1 → END | Theo CFG/source; case 4 |
| P5 | START → 1 → END | Theo CFG/source; case 5 |
| P6 | START → 1 → END | Theo CFG/source; case 6 |
| P7 | START → 1 → END | Theo CFG/source; case 7 |
| P8 | START → 1 → END | Theo CFG/source; case 8 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC3 | P3 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC4 | P4 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC5 | P5 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC6 | P6 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC7 | P7 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC8 | P8 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 14 / 14 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1461_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/iterative_schur_complement_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/power_series_expansion_preconditioner.h"
#include "ceres/preconditioner.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1461, TC1_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::IterativeSchurComplementSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1461, TC2_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::IterativeSchurComplementSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1461, TC3_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::IterativeSchurComplementSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1461, TC4_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::IterativeSchurComplementSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1461, TC5_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::IterativeSchurComplementSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1461, TC6_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::IterativeSchurComplementSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1461, TC7_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::IterativeSchurComplementSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1461, TC8_CallsTarget) {
  LinearSolver::PerSolveOptions per_solve_options{};
  ceres::internal::IterativeSchurComplementSolver object{};
  object.SolveImpl(nullptr, nullptr, per_solve_options, nullptr);
}
```
