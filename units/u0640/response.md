# Unit u0640
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 196 → 197 → END | Không có điểm rẽ nhánh. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

`cfg.txt` không tồn tại cho unit này; không bịa CFG. Các nhánh được đối chiếu theo CFG trong prompt.md.
Không có nhánh điều khiển trong CFG.
C2 dự kiến = 0 / 0.

## D. File test

```cpp
// FILE: u0640_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_cost_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0640, CallsTarget) {
  object.NumericDiffCostFunction({});
}
```
