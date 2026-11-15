# Unit u0547
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
C2 dự kiến = 4 / 4.

## D. File test

```cpp
// FILE: u0547_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> 2 -> 3 -> END.
TEST(Unit_u0547, PathP1) {
  ceres::Jet<double, 2> x(1.0), y(2.0);
  ceres::fmin(x, y);
}
```
