# Unit u0499
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | Không có điểm rẽ nhánh. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không có nhánh điều khiển trong CFG.
C2 dự kiến = 0 / 0.

## D. File test

```cpp
// FILE: u0499_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0499, PathP1) {
  double z_0[4] = {};
  double w_1[4] = {};
  double zw_2[4] = {};
  ceres::QuaternionProduct<double>(z_0, w_1, zw_2);
}
```
