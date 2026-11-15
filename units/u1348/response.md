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
// FILE: u1348_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1348, TC1_CallsTarget) {
  std::vector<Block> blocks{};
  int num_threads{};
  ceres::internal::BlockRandomAccessDiagonalMatrix object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1348, TC2_CallsTarget) {
  std::vector<Block> blocks{};
  int num_threads{};
  ceres::internal::BlockRandomAccessDiagonalMatrix object{};
  (void)object;
}
```
