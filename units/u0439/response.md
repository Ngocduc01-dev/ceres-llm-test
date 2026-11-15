# Unit u0439
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |

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
// FILE: u0439_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0439, PathP1) {
  const JetT& arg_0{}
  const JetT& arg_0{};
  JetT* arg_1 = nullptr;
  ceres::CubicInterpolator<Grid1D<double, 2>>::Evaluate<Jet<double, 4>> target(arg_0, arg_1);
  target.Evaluate(arg_0, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0439, PathP2) {
  const JetT& arg_0{}
  const JetT& arg_0{};
  JetT* arg_1 = nullptr;
  ceres::CubicInterpolator<Grid1D<double, 2>>::Evaluate<Jet<double, 4>> target(arg_0, arg_1);
  target.Evaluate(arg_0, nullptr);
}
```
