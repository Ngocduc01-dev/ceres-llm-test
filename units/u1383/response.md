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
// FILE: u1383_test.cc
#include "gtest/gtest.h"
#include "ceres/block_evaluate_preparer.h"
#include "ceres/block_jacobian_writer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1383, TC1_CallsTarget) {
  unsigned int num_threads{};
  ceres::internal::BlockJacobianWriter object{};
  object.CreateEvaluatePreparers(num_threads);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1383, TC2_CallsTarget) {
  unsigned int num_threads{};
  ceres::internal::BlockJacobianWriter object{};
  object.CreateEvaluatePreparers(num_threads);
}
```
