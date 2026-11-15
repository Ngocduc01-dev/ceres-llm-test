**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào. Đường đi duy nhất. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `v`: vector 4 phần tử, khác 0. `beta`: số thực (dùng `2/‖v‖²`). `x`: vector 4 phần tử. `delta`: vector 3 phần tử. `norm_delta`: (0, π], khác 0 để tránh chia cho 0. | `v=(1, 0.2, -0.3, 0.4)`, `beta=2/‖v‖²≈1.55`, `x=(0.5, -1, 2, 1.5)`, `delta=(0.3, 0.4, 0)`, `norm_delta=0.5` |

Các giá trị được cố định trực tiếp trong code, không dùng số ngẫu nhiên, nên mỗi lần chạy cho cùng kết quả.

**C. Nhánh không test**

Không có. Hàm có 0 điểm rẽ nhánh, nên tổng số nhánh là 0 và P1 là đường đi duy nhất.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; TC1 đi qua toàn bộ node 1, dự kiến chạy thật, chưa chạy).

**D. File test**

```cpp
// FILE: u0062_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/sphere_manifold_functions.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ComputeSphereManifoldPlusTest, TC1_SinglePath) {
  using Vec4 = Eigen::Matrix<double, 4, 1>;
  using Vec3 = Eigen::Matrix<double, 3, 1>;

  Vec4 v;
  v << 1.0, 0.2, -0.3, 0.4;
  const double beta = 2.0 / v.squaredNorm();

  double x_data[4] = {0.5, -1.0, 2.0, 1.5};
  double delta_data[3] = {0.3, 0.4, 0.0};
  double out_data[4] = {0.0, 0.0, 0.0, 0.0};

  Eigen::Map<const Vec4> x(x_data);
  Eigen::Map<const Vec3> delta(delta_data);
  Eigen::Map<Vec4> x_plus_delta(out_data);
  const double norm_delta = 0.5;

  ComputeSphereManifoldPlus(v, beta, x, delta, norm_delta, &x_plus_delta);
}

}  // namespace internal
}  // namespace ceres
```