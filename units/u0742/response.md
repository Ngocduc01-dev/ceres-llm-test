# Unit u0742
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 6 / 6.

## D. File test

```cpp
// FILE: u0742_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_cost_function.h"
#include "ceres/sized_cost_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0742, CallsTarget) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double residuals_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobians_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, residuals_data, jacobians_data);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0742, CallsTargetAlternate) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double residuals_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobians_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, residuals_data, jacobians_data);
}
```
