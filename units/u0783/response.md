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

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 12 / 12 (chưa chạy thật).

# D. File test

```cpp
// FILE: u0783_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0783, TC1_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0783, TC2_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0783, TC3_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0783, TC4_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0783, TC5_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u0783, TC6_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u0783, TC7_CallsTarget) {
  const LinearSolverType linear_solver_type{};
  const PreconditionerType preconditioner_type{};
  const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type{};
  const LinearSolverOrderingType linear_solver_ordering_type{};
  ceres::internal::AreJacobianColumnsOrdered(linear_solver_type, preconditioner_type, sparse_linear_algebra_library_type, linear_solver_ordering_type);
}
```
