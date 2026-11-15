**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 vòng lặp), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x`: mảng 4 double (quaternion), không có ràng buộc từ điều kiện đường đi, chọn trong [-1, 1]; `jacobian`: mảng 4×3 = 12 double (ghi ra, giá trị ban đầu không quan trọng) | `x` = {0.5, -0.5, 0.5, 0.5} (sinh bằng seed cố định rồi chọn; đã chọn sẵn một quaternion đơn vị); `jacobian` = 12 phần tử khởi tạo 0 |

**C. Nhánh không test**

Không có. CFG khớp với mã nguồn (dòng 299–300: gọi `QuaternionPlusJacobianImpl<EigenQuaternionOrder>` rồi `return true`).

`C2 dự kiến = 0 / 0` (không có nhánh nào; tổng số nhánh = 2 × 0 = 0, nên coi như phủ đầy đủ khi node 1 được chạy qua).

**D. File test**

```cpp
// FILE: u0347_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EigenQuaternionManifoldPlusJacobianTest, P1_SingleStraightLinePath) {
  ceres::EigenQuaternionManifold manifold;
  // Thứ tự Eigen: (x, y, z, w). Quaternion đơn vị.
  const double x[4] = {0.5, -0.5, 0.5, 0.5};
  // Jacobian kích thước AmbientSize x TangentSize = 4 x 3, lưu theo hàng.
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}
```