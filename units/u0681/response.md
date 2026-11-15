# Unit u0681
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
// FILE: u0681_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"
#include "ceres/line_search_minimizer.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0681, PathP1) {
  ceres::internal::SteepestDescent target;
  ceres::internal::LineSearchMinimizer::State previous{};
  ceres::internal::LineSearchMinimizer::State current{};
  current.gradient = ceres::internal::Vector::Zero(1);
  ceres::internal::Vector search_direction(1);
  target.NextDirection(previous, current, &search_direction);
}
```
