# Unit u0351
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
// FILE: u0351_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include <set>

// Path P1: START -> 1 -> END.
TEST(Unit_u0351, PathP1) {
  std::set<int> collection;
  ceres::ContainsKey(collection, 1);
}
```
