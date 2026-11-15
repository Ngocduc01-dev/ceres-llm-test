# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 0 / 0 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1258_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1258, TC1_CallsTarget) {
  )(const std::pair<T, T> p{};
  ceres::internal::pair_hash object{};
  object(p);
}
```
