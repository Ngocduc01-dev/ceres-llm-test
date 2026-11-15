**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x[3]`, `delta[3]`: mỗi phần tử trong [-5, 5]; `x_plus_delta[3]` là bộ nhớ đầu ra, giá trị khởi tạo bằng 0 | Sinh bằng `std::mt19937` với seed cố định 42 và `uniform_real_distribution<double>(-5, 5)` |

**C. Nhánh không test:** không có. Hàm không có điểm rẽ nhánh và không có `CHECK`, nên tổng số nhánh là 0 và một test đi hết đường duy nhất.

`C2 dự kiến = 0 / 0` (không có nhánh, tương đương 100%; node 1 được phủ hoàn toàn bởi TC1; chưa chạy thật).

**D. File test**

```cpp
// FILE: u0007_test.cc
#include <random>

#include "ceres/autodiff_manifold.h"
#include "gtest/gtest.h"

namespace ceres {
namespace {

// Functor kiểu Euclidean dùng để khởi tạo AutoDiffManifold<EuclideanFunctor, 3, 3>.
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

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(AutoDiffManifoldPlusTest, TC1_P1_SingleStatementReturn) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);

  double x[3];
  double delta[3];
  double x_plus_delta[3] = {0.0, 0.0, 0.0};
  for (int i = 0; i < 3; ++i) {
    x[i] = dist(gen);
    delta[i] = dist(gen);
  }

  AutoDiffManifold<EuclideanFunctor, 3, 3> manifold(new EuclideanFunctor);
  (void)manifold.Plus(x, delta, x_plus_delta);
}

}  // namespace
}  // namespace ceres
```