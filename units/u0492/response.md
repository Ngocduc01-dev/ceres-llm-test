# Unit u0492
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
// FILE: u0492_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_step_evaluator.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0492, PathP1) {
  const double arg_0 = 1.0;
  const double arg_1 = 1.0;
  ceres::internal::TrustRegionStepEvaluator target(arg_0, arg_1);
  target.StepQuality(1.0, 1.0);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0492, PathP2) {
  const double arg_0 = 1.0;
  const double arg_1 = 1.0;
  ceres::internal::TrustRegionStepEvaluator target(arg_0, arg_1);
  target.StepQuality(1.0, 1.0);
}
```
