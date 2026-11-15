# Unit u0701
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
// FILE: u0701_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0701, PathP1) {
  ceres::internal::Block left(1, 0);
  ceres::internal::Block right(1, 0);
  left == right;
}
```
