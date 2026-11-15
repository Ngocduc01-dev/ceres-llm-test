# Unit u0566
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
// FILE: u0566_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"
#include <utility>

// Path P1: START -> 1 -> END.
TEST(Unit_u0566, PathP1) {
  ceres::SubsetManifold first(2, {1});
  ceres::SubsetManifold second(2, {0});
  ceres::ProductManifold<ceres::SubsetManifold, ceres::SubsetManifold> target(
      std::index_sequence<0, 1>{}, first, second);
}
```
