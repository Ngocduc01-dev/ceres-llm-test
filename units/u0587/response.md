# Unit u0587
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 2 / 2.

## D. File test

```cpp
// FILE: u0587_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0587, CallsTarget) {
  double y_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double y_minus_x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.MinusImpl(y_data, x_data, y_minus_x_data, {});
}
```
