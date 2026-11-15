# Unit u0437
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
// FILE: u0437_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"
#include "ceres/sized_cost_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0437, PathP1) {
  const double *const * arg_0 = nullptr;
  double * arg_1 = nullptr;
  double ** arg_2 = nullptr;
  ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2> target(arg_0, arg_1, arg_2);
  target.Evaluate(nullptr, nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0437, PathP2) {
  const double *const * arg_0 = nullptr;
  double * arg_1 = nullptr;
  double ** arg_2 = nullptr;
  ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2> target(arg_0, arg_1, arg_2);
  target.Evaluate(nullptr, nullptr, nullptr);
}
```
