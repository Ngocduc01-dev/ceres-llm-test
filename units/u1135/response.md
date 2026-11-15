# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |
| P3 | START → 1 → END | Theo CFG/source; case 3 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC3 | P3 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 4 / 4 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1135_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parallel_for.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1135, TC1_CallsTarget) {
  Chunk chunk{};
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.UpdateRhs(chunk, A, nullptr, row_block_counter, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1135, TC2_CallsTarget) {
  Chunk chunk{};
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.UpdateRhs(chunk, A, nullptr, row_block_counter, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1135, TC3_CallsTarget) {
  Chunk chunk{};
  BlockSparseMatrixData A{};
  int row_block_counter{};
  ceres::internal::SchurEliminator object{};
  object.UpdateRhs(chunk, A, nullptr, row_block_counter, nullptr, nullptr);
}
```
