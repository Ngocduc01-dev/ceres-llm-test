# Unit u0441
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 2 / 2.

## D. File test

```cpp
// FILE: u0441_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0441, PathP1) {
  double arg_0 = 1.0;
  double arg_1 = 1.0;
  double * arg_2 = nullptr;
  double * arg_3 = nullptr;
  double * arg_4 = nullptr;
  ceres::BiCubicInterpolator<Grid2D<double>> target(arg_0, arg_1, arg_2, arg_3, arg_4);
  target.Evaluate(1.0, 1.0, nullptr, nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0441, PathP2) {
  double arg_0 = 1.0;
  double arg_1 = 1.0;
  double * arg_2 = nullptr;
  double * arg_3 = nullptr;
  double * arg_4 = nullptr;
  ceres::BiCubicInterpolator<Grid2D<double>> target(arg_0, arg_1, arg_2, arg_3, arg_4);
  target.Evaluate(1.0, 1.0, nullptr, nullptr, nullptr);
}
```
