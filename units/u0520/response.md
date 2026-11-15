# Unit u0520
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 6 / 6.

## D. File test

```cpp
// FILE: u0520_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0520, CallsTarget) {
  double x_ptr_data[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_plus_delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Plus(x_ptr_data, delta_ptr_data, x_plus_delta_ptr_data);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0520, CallsTargetAlternate) {
  double x_ptr_data[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_plus_delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Plus(x_ptr_data, delta_ptr_data, x_plus_delta_ptr_data);
}
```
