# Unit u0472
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
// FILE: u0472_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 → 2 → END (rho_ is null).
TEST(Unit_u0472, PathP1) {
  double rho[3] = {};
  ceres::ScaledLoss target(nullptr, 2.0, ceres::DO_NOT_TAKE_OWNERSHIP);
  target.Evaluate(1.0, rho);
}

// Path P2: START -> 1 → 3 → END (rho_ is non-null).
TEST(Unit_u0472, PathP2) {
  double rho[3] = {};
  ceres::TrivialLoss inner;
  ceres::ScaledLoss target(&inner, 2.0, ceres::DO_NOT_TAKE_OWNERSHIP);
  target.Evaluate(1.0, rho);
}
```
