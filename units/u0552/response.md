# Unit u0552
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10 → 11 → 12 → 13 → 14 → 15 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 8 / 8.

## D. File test

```cpp
// FILE: u0552_test.cc
#include "gtest/gtest.h"
#include "ceres/corrector.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0552, CallsTarget) {
  double residuals_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobian_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.CorrectJacobian(1, 1, residuals_data, jacobian_data);
}
```
