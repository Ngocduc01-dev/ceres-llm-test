**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Node 1: `return 3` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Template `<EuclideanFunctor, 3, 3>`, object tạo bằng constructor mặc định | Không có |

**C. Nhánh không test**

Không có nhánh nào. Hàm có 0 điểm rẽ nhánh nên tổng số nhánh là 0. Một test đi qua toàn bộ đường đi duy nhất, tức mọi node (1) của CFG.
`C2 dự kiến = 0 / 0` (không có nhánh nào; đường đi duy nhất P1 được phủ hoàn toàn, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0005_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace ceres {
namespace {

// Functor kiểu Euclidean 3 chiều, dùng để khởi tạo template AutoDiffManifold.
struct EuclideanFunctor {
  template <typename T>
  bool operator()(const T* x, const T* delta, T* x_plus_delta) const {
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

// P1: START -> 1 -> END
TEST(AutoDiffManifoldAmbientSizeTest, TC1_ReturnAmbientSize) {
  AutoDiffManifold<EuclideanFunctor, 3, 3> manifold;
  manifold.AmbientSize();
}

}  // namespace
}  // namespace ceres
```