# Unit u0712
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | Không có điểm rẽ nhánh. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không có nhánh điều khiển trong CFG.
C2 dự kiến = 0 / 0.

## D. File test

```cpp
// FILE: u0712_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0712, CallsTarget) {
  double function_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.GradientProblem(function_data);
}
```
