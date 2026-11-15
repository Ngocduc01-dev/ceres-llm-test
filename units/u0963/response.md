# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. Không có cfg.txt; không bịa CFG/C2.

C2 dự kiến = không xác định vì thiếu cfg.txt; không bịa nhánh (chưa chạy thật).

# D. File test

```cpp
// FILE: u0963_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/parameter_block.h"
#include "ceres/triplet_sparse_matrix.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0963, TC1_CallsTarget) {
  const LinearSolverOrderingType linear_solver_ordering_type{};
  TripletSparseMatrix tsm_block_jacobian_transpose{};
  ParameterBlockOrdering parameter_block_ordering{};
  ceres::internal::(anonymous)::OrderingForSparseNormalCholeskyUsingSuiteSparse(linear_solver_ordering_type, tsm_block_jacobian_transpose, nullptr, parameter_block_ordering, nullptr);
}
```
