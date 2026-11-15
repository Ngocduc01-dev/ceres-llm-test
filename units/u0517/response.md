# Unit u0517
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 4 / 4.

## D. File test

```cpp
// FILE: u0517_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/sphere_manifold_functions.h"

// Path P1: START -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> END.
TEST(Unit_u0517, PathP1) {
  Eigen::Matrix<double, 2, 1> v; v << 1.0, 0.0;
  Eigen::Matrix<double, 2, 1> x; x << 1.0, 0.0;
  Eigen::Matrix<double, 2, 1> y; y << 0.0, 1.0;
  Eigen::Matrix<double, 1, 1> y_minus_x;
  ceres::internal::ComputeSphereManifoldMinus(v, 1.0, x, y, &y_minus_x);
}
```
