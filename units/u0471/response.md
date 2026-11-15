**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → 3 → END | node 1: sai |

Hàm không có vòng lặp. CFG khớp với mã nguồn.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `a` = 2.0 nên `a_squared_` = 4.0. Cần `s <= 4.0`, tức `s` ∈ (−∞, 4.0]. Chọn trong [0, 4]. | `a = 2.0`, `s = 1.5` |
| TC2 | P2 | `a` = 2.0 nên `a_squared_` = 4.0. Cần `s > 4.0`, tức `s` ∈ (4.0, +∞). Chọn trong (4, 10]. | `a = 2.0`, `s = 7.3` |

**C. Nhánh không test**

Không có. Cả hai nhánh của node 1 đều đi tới được, và hàm không có `CHECK`.

`C2 dự kiến = 2 / 2` (dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u0471_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(TukeyLossEvaluateTest, InlierRegion) {
  ceres::TukeyLoss loss(2.0);
  double rho[3] = {0.0, 0.0, 0.0};
  loss.Evaluate(1.5, rho);
}

// P2: START -> 1 -> 3 -> END (node 1: sai)
TEST(TukeyLossEvaluateTest, OutlierRegion) {
  ceres::TukeyLoss loss(2.0);
  double rho[3] = {0.0, 0.0, 0.0};
  loss.Evaluate(7.3, rho);
}
```