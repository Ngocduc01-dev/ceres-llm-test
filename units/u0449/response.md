# Unit u0449
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 2 / 2.

## D. File test

```cpp
// FILE: u0449_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/sphere_manifold_functions.h"

// Path P1: START -> 1 -> 2 -> 3 -> 4 -> 2 -> 5 -> END.
TEST(Unit_u0449, PathP1) {
  Eigen::Matrix<double, 4, 1> x;
  x << 1.0, 0.0, 0.0, 0.0;
  Eigen::Matrix<double, 4, 3> jacobian;
  ceres::internal::ComputeSphereManifoldPlusJacobian(x, &jacobian);
}
```
