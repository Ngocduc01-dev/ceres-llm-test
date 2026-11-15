# Unit u0473
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
// FILE: u0473_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include <unordered_map>

// Path P1: START -> 1 -> END.
TEST(Unit_u0473, PathP1) {
  std::unordered_map<int, double> collection;
  collection.emplace(1, 2.0);
  ceres::FindOrDie(collection, 1);
}
```
