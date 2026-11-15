# Unit u0743
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 4 / 4.

## D. File test

```cpp
// FILE: u0743_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/internal/variadic_evaluate.h"
#include "ceres/numeric_diff_first_order_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0743, CallsTarget) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cost_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double gradient_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, cost_data, gradient_data);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0743, CallsTargetAlternate) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cost_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double gradient_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, cost_data, gradient_data);
}
```
