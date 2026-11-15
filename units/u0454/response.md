**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng (`rho_` là nullptr) |
| P2 | START → 1 → 3 → END | node 1: sai (`rho_` khác nullptr) |

Hàm không có vòng lặp. CFG khớp với mã nguồn.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `rho` = nullptr; `sq_norm` ∈ [0, 10] | `rho` = nullptr, `sq_norm` = 2.5 |
| TC2 | P2 | `rho` ≠ nullptr (ví dụ `TrivialLoss`); `sq_norm` ∈ [0, 10] | `rho` = `new TrivialLoss()`, `sq_norm` = 3.7 |

**C. Nhánh không test**

Không có. Cả 2 nhánh đều có test.

C2 dự kiến = 2 / 2

**D. File test**

```cpp
// FILE: u0454_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: node 1: đúng -> node 2 -> END
TEST(LossFunctionWrapperEvaluateTest, NullRhoUsesDefaultValues) {
  ceres::LossFunctionWrapper wrapper(nullptr, ceres::TAKE_OWNERSHIP);
  double sq_norm = 2.5;
  double out[3] = {0.0, 0.0, 0.0};
  wrapper.Evaluate(sq_norm, out);
}

// P2: node 1: sai -> node 3 -> END
TEST(LossFunctionWrapperEvaluateTest, NonNullRhoDelegatesToLossFunction) {
  ceres::LossFunctionWrapper wrapper(new ceres::TrivialLoss(),
                                     ceres::TAKE_OWNERSHIP);
  double sq_norm = 3.7;
  double out[3] = {0.0, 0.0, 0.0};
  wrapper.Evaluate(sq_norm, out);
}
```