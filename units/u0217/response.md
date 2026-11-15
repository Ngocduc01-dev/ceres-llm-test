**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm), nên CFG chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Object `SphereManifold<4>` tạo bằng constructor mặc định (size_ = 4). `x_ptr`: 4 số thực trong [-1, 1], không đồng thời bằng 0. `jacobian_ptr`: bộ đệm 12 phần tử (ma trận 3×4) | `x = {0.37, -0.62, 0.81, 0.15}`; `jacobian` = 12 số 0.0 |

Ghi chú: `jacobian_ptr` cần 12 phần tử, vượt giới hạn 5 phần tử của mục 4. Đây là kích thước bắt buộc, vì hàm ghi vào ma trận (size_ − 1) × size_ = 3 × 4.

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh và cũng không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, mọi đường đi đều được phủ, tức 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0217_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SphereManifoldMinusJacobian, TC1_P1_SinglePath) {
  ceres::SphereManifold<4> manifold;
  const double x[4] = {0.37, -0.62, 0.81, 0.15};
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  static_cast<void>(manifold.MinusJacobian(x, jacobian));
}
```