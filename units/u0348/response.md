**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh), CFG chỉ có một đường đi duy nhất. Không có vòng lặp và không có `CHECK`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (0 điểm rẽ nhánh); node 1 gọi `QuaternionMinusImpl<EigenQuaternionOrder>(y, x, y_minus_x)` rồi `return true` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `y`, `x`: mảng 4 double (quaternion Eigen: x, y, z, w), mỗi phần tử trong [-1, 1]. `y_minus_x`: mảng 3 double (không gắn điều kiện). Không có điều kiện đường đi nên mọi giá trị đều hợp lệ. | Sinh bằng `std::mt19937` seed 42 và `std::uniform_real_distribution<double>(-1.0, 1.0)`. Mỗi quaternion được chuẩn hoá về độ dài 1 (nếu chuẩn quá nhỏ thì dùng {0, 0, 0, 1}). `y_minus_x` khởi tạo {0, 0, 0}. |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (không có điểm rẽ nhánh nào, không có nhánh `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh ở node 1 đều được chạy qua bởi TC1, nên độ phủ câu lệnh là 100%).

**D. File test**

```cpp
// FILE: u0348_test.cc
#include <cmath>
#include <random>

#include "ceres/manifold.h"
#include "gtest/gtest.h"

namespace ceres {

namespace {

// Sinh quaternion Eigen (thứ tự x, y, z, w) ngẫu nhiên đã chuẩn hoá.
void MakeUnitQuaternion(std::mt19937& gen, double* q) {
  std::uniform_real_distribution<double> dist(-1.0, 1.0);
  double norm = 0.0;
  for (int i = 0; i < 4; ++i) {
    q[i] = dist(gen);
    norm += q[i] * q[i];
  }
  norm = std::sqrt(norm);
  if (norm < 1e-3) {
    q[0] = 0.0;
    q[1] = 0.0;
    q[2] = 0.0;
    q[3] = 1.0;
    return;
  }
  for (int i = 0; i < 4; ++i) {
    q[i] /= norm;
  }
}

}  // namespace

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(EigenQuaternionManifoldMinus, StraightLinePath) {
  std::mt19937 gen(42);
  double y[4];
  double x[4];
  double y_minus_x[3] = {0.0, 0.0, 0.0};
  MakeUnitQuaternion(gen, y);
  MakeUnitQuaternion(gen, x);

  EigenQuaternionManifold manifold;
  manifold.Minus(y, x, y_minus_x);
}

}  // namespace ceres
```