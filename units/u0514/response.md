# Unit u0514
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 2 / 2.

## D. File test

```cpp
// FILE: u0514_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0514, CallsTarget) {
  double f_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.GetValue(1, f_data);
}
```
