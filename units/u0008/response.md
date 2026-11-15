**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x[3]`, `y[3]`: mỗi phần tử trong [-10, 10]. `y_minus_x[3]`: mảng đầu ra, giá trị khởi tạo bất kỳ. Không có điều kiện đường đi nào ràng buộc thêm. | Sinh bằng `std::mt19937` với seed cố định 42 và `uniform_real_distribution<double>(-10, 10)` |

**C. Nhánh không test**

Không có. Hàm có 0 điểm rẽ nhánh, không có vòng lặp và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào, nên coi như đạt 100% khi node 1 được chạy qua; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0008_test.cc
#include <random>

#include "ceres/autodiff_manifold.h"
#include "gtest/gtest.h"

namespace {

// Functor Euclidean dùng cho AutoDiffManifold<EuclideanFunctor, 3, 3>.
struct EuclideanFunctor {
  template <typename T>
  bool Plus(const T* x, const T* delta, T* x_plus_delta) const {
    for (int i = 0; i < 3; ++i) {
      x_plus_delta[i] = x[i] + delta[i];
    }
    return true;
  }

  template <typename T>
  bool Minus(const T* y, const T* x, T* y_minus_x) const {
    for (int i = 0; i < 3; ++i) {
      y_minus_x[i] = y[i] - x[i];
    }
    return true;
  }
};

}  // namespace

// TC1 - Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(AutoDiffManifoldMinusTest, TC1_P1_CallFunctorMinus) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-10.0, 10.0);

  double x[3];
  double y[3];
  double y_minus_x[3] = {0.0, 0.0, 0.0};
  for (int i = 0; i < 3; ++i) {
    x[i] = dist(gen);
    y[i] = dist(gen);
  }

  ceres::AutoDiffManifold<EuclideanFunctor, 3, 3> manifold;
  manifold.Minus(y, x, y_minus_x);
}
```