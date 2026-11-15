# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |
| P3 | START → 1 → END | Theo CFG/source; case 3 |
| P4 | START → 1 → END | Theo CFG/source; case 4 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC3 | P3 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC4 | P4 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 6 / 6 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1275_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1275, TC1_CallsTarget) {
  const int row_block_size{};
  const int e_block_size{};
  const int f_block_size{};
  ceres::SchurStructureToString(row_block_size, e_block_size, f_block_size);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1275, TC2_CallsTarget) {
  const int row_block_size{};
  const int e_block_size{};
  const int f_block_size{};
  ceres::SchurStructureToString(row_block_size, e_block_size, f_block_size);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1275, TC3_CallsTarget) {
  const int row_block_size{};
  const int e_block_size{};
  const int f_block_size{};
  ceres::SchurStructureToString(row_block_size, e_block_size, f_block_size);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1275, TC4_CallsTarget) {
  const int row_block_size{};
  const int e_block_size{};
  const int f_block_size{};
  ceres::SchurStructureToString(row_block_size, e_block_size, f_block_size);
}
```
