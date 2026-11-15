# Unit u0454
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
// FILE: u0454_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: node 1: đúng -> node 2 -> END
// Path P1: START -> CFG nodes -> END.
TEST(LossFunctionWrapperEvaluateTest, NullRhoUsesDefaultValues) {
  ceres::LossFunctionWrapper wrapper(nullptr, ceres::TAKE_OWNERSHIP);
  double sq_norm = 2.5;
  double out[3] = {0.0, 0.0, 0.0};
  wrapper.Evaluate(sq_norm, out);
}

// P2: node 1: sai -> node 3 -> END
// Path P1: START -> CFG nodes -> END.
TEST(LossFunctionWrapperEvaluateTest, NonNullRhoDelegatesToLossFunction) {
  ceres::LossFunctionWrapper wrapper(new ceres::TrivialLoss(),
                                     ceres::TAKE_OWNERSHIP);
  double sq_norm = 3.7;
  double out[3] = {0.0, 0.0, 0.0};
  wrapper.Evaluate(sq_norm, out);
}
```
