# Unit u0469
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
// FILE: u0469_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> 2 -> END (node 1: đúng)
// Path P1: START -> CFG nodes -> END.
TEST(HuberLossEvaluate, OutlierRegion) {
  ceres::HuberLoss loss(2.0);  // b_ = 4.0
  double rho[3] = {0.0, 0.0, 0.0};
  loss.Evaluate(7.3, rho);     // s > b_
}

// P2: START -> 1 -> 3 -> END (node 1: sai)
// Path P1: START -> CFG nodes -> END.
TEST(HuberLossEvaluate, InlierRegion) {
  ceres::HuberLoss loss(2.0);  // b_ = 4.0
  double rho[3] = {0.0, 0.0, 0.0};
  loss.Evaluate(2.1, rho);     // s <= b_
}
```
