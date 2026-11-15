**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; đi tuần tự node 1 (gọi `QuaternionMinusJacobianImpl`, `return true`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x`: mảng 4 double (quaternion), không có điều kiện đường đi ràng buộc; chọn trong [-1, 1]. `jacobian`: mảng 12 double (ma trận 4×3), giá trị khởi tạo bất kỳ | `x = {0.5, -0.5, 0.5, -0.5}` (seed cố định 0 với ngẫu nhiên, ở đây ghi trực tiếp giá trị); `jacobian` khởi tạo 0 |

**C. Nhánh không test**

Không có (hàm không có điểm rẽ nhánh, tổng số nhánh = 0). Ghi chú: CFG khớp với mã nguồn.

`C2 dự kiến = 0 / 0` (không có nhánh; toàn bộ câu lệnh node 1 được thực thi bởi TC1, tức phủ 100% câu lệnh)

**D. File test**

```cpp
// FILE: u0345_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END
TEST(QuaternionManifoldMinusJacobian, TC1_P1_SequentialPath) {
  ceres::QuaternionManifold manifold;
  const double x[4] = {0.5, -0.5, 0.5, -0.5};
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.MinusJacobian(x, jacobian);
}
```