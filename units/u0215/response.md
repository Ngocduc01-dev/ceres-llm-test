**A. Test paths**

Hàm có 0 điểm rẽ nhánh, nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (đường đi tuyến tính) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `SphereManifold<4>` (size_ = 4). `x_ptr`: 4 phần tử, mỗi phần tử thuộc [-2, 2], vectơ khác 0. `jacobian_ptr`: buffer 4×3 = 12 double (bắt buộc theo kích thước ma trận Jacobian). | `x = {0.5, -1.0, 1.5, 0.75}`; `jacobian` gồm 12 phần tử khởi tạo 0 |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh và không có `CHECK` trong thân hàm. Mã nguồn khớp với CFG.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên coi là đạt 100%; node 1 được chạy qua bởi TC1; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0215_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SphereManifoldPlusJacobian, TC1_LinearPath) {
  ceres::SphereManifold<4> manifold;
  const double x[4] = {0.5, -1.0, 1.5, 0.75};
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}
```