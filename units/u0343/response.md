**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (hàm chỉ có 1 đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x`: mảng 4 double (quaternion), mỗi phần tử trong [-1, 1], không có điều kiện đường đi nào ràng buộc thêm. `jacobian`: mảng 12 double (ma trận 4×3), giá trị ban đầu tùy ý. | `x = {0.5, 0.5, 0.5, 0.5}`, `jacobian` = 12 phần tử khởi tạo bằng 0 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.

C2 dự kiến = 0 / 0. Hàm không có nhánh nào, nên mẫu số bằng 0. Test TC1 chạy qua toàn bộ node 1 và `return true`.

**D. File test**

```cpp
// FILE: u0343_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionManifoldPlusJacobianTest, TC1_SinglePath) {
  ceres::QuaternionManifold manifold;
  const double x[4] = {0.5, 0.5, 0.5, 0.5};
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}
```