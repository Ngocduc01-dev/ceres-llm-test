# Unit u0622
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không có nhánh điều khiển trong CFG.
C2 dự kiến = 0 / 0.

## D. File test

```cpp
// FILE: u0622_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"
#include "ceres/numeric_diff_options.h"

struct LocalCostFunctor {};
// Path P1: START -> 1 -> END.
TEST(Unit_u0622, PathP1) {
  ceres::DynamicNumericDiffCostFunction<LocalCostFunctor, ceres::RIDDERS> target(
      nullptr, ceres::TAKE_OWNERSHIP);
}
```
