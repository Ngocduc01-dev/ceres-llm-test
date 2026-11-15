# Unit u0550
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 6 / 6.

## D. File test

```cpp
// FILE: u0550_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0550, CallsTarget) {
  double x_ptr_data[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double y_ptr_data[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.RightMultiplyAndAccumulate(x_ptr_data, y_ptr_data);
}
```
