# Unit u0475
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 99 → 100 → 101 → 102 → 103 → 104 → 105 → 106 → 107 → 108 → END | Không có điểm rẽ nhánh. |

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
// FILE: u0475_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0475, PathP1) {
  std::map<int, int> collection{{1, 2}};
  ceres::FindOrNull(collection, 1);
}
```
