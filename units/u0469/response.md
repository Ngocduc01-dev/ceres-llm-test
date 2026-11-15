**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → 3 → END | node 1: sai |

Hàm không có vòng lặp, nên không cần thiết kế số lần lặp.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `a` = 2.0, nên `b_` = a² = 4.0. Điều kiện `s > b_` đúng khi s ∈ (4, 100]. | `a` = 2.0, `s` = 7.3 |
| TC2 | P2 | `a` = 2.0, nên `b_` = 4.0. Điều kiện `s > b_` sai khi s ∈ [−100, 4]. | `a` = 2.0, `s` = 2.1 |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Trong đó, `std::max` ở node 2 là lời gọi hàm nên không tính là điểm rẽ nhánh.

C2 dự kiến = 2 / 2 (100%, dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u0469_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(HuberLossEvaluate, OutlierRegion) {
  ceres::HuberLoss loss(2.0);  // b_ = 4.0
  double rho[3] = {0.0, 0.0, 0.0};
  loss.Evaluate(7.3, rho);     // s > b_
}

// P2: START -> 1 -> 3 -> END (node 1: sai)
TEST(HuberLossEvaluate, InlierRegion) {
  ceres::HuberLoss loss(2.0);  // b_ = 4.0
  double rho[3] = {0.0, 0.0, 0.0};
  loss.Evaluate(2.1, rho);     // s <= b_
}
```