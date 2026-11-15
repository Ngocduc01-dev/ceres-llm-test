**A. Test paths**

Hàm không có điểm rẽ nhánh nào (tổng số nhánh = 0), chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `EuclideanManifold<DYNAMIC>(size)` với size từ 1 đến 5; `x`, `y` là mảng double size phần tử, giá trị tuỳ ý (−10 đến 10); `y_minus_x` là mảng size phần tử | size = 3; x = {1.5, −2.0, 4.0}; y = {0.5, 3.0, −1.0}; y_minus_x = {0, 0, 0} |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp (phép trừ Eigen không thể hiện thành vòng lặp trong CFG). Không có `CHECK` trong hàm.

C2 dự kiến = 0 / 0 (không có nhánh nào; mọi câu lệnh ở node 1 đều được chạy bởi TC1, nên đạt C1 = 100%).

**D. File test**

```cpp
// FILE: u0183_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldMinus, P1_SinglePath) {
  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(3);
  const double x[3] = {1.5, -2.0, 4.0};
  const double y[3] = {0.5, 3.0, -1.0};
  double y_minus_x[3] = {0.0, 0.0, 0.0};
  manifold.Minus(y, x, y_minus_x);
}
```