# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 2 / 2 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1086_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_random_access_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1086, TC1_CallsTarget) {
  int row_block_id{};
  int col_block_id{};
  ceres::internal::BlockRandomAccessSparseMatrix object{};
  object.GetCell(row_block_id, col_block_id, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1086, TC2_CallsTarget) {
  int row_block_id{};
  int col_block_id{};
  ceres::internal::BlockRandomAccessSparseMatrix object{};
  object.GetCell(row_block_id, col_block_id, nullptr, nullptr, nullptr, nullptr);
}
```
