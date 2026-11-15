# Unit u0596
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 2 / 2.

## D. File test

```cpp
// FILE: u0596_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.cc"

namespace ceres {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0596, CallsTarget) {
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double delta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_plus_delta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  QuaternionPlusImpl(x_data, delta_data, x_plus_delta_data);
}
}  // namespace ceres
```
