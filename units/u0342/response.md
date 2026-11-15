**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; đi thẳng qua node 1 (gọi `QuaternionPlusImpl`, `return true`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x`: mảng 4 double (bất kỳ, hàm không có điều kiện nên không ràng buộc); `delta`: mảng 3 double (bất kỳ); `x_plus_delta`: mảng 4 double (đầu ra) | `x = {1.0, 0.0, 0.0, 0.0}`, `delta = {0.3, -0.2, 0.5}` (chọn cố định, không dùng sinh số ngẫu nhiên nên không cần seed), `x_plus_delta = {0, 0, 0, 0}` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên C2 mặc định đạt 100%; node 1 được phủ bởi TC1, tức C1 = 100%).

**D. File test**

```cpp
// FILE: u0342_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionManifoldPlusTest, TC1_StraightLinePath) {
  ceres::QuaternionManifold manifold;
  const double x[4] = {1.0, 0.0, 0.0, 0.0};
  const double delta[3] = {0.3, -0.2, 0.5};
  double x_plus_delta[4] = {0.0, 0.0, 0.0, 0.0};
  manifold.Plus(x, delta, x_plus_delta);
}
```