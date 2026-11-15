// FILE: u0006_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace {

// Functor Euclid đơn giản (tự định nghĩa) dùng cho AutoDiffManifold.
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

}  // namespace

// P1: START -> 1 -> END (không có nhánh rẽ)
TEST(AutoDiffManifoldTangentSizeTest, TC1_P1_ReturnTangentSize) {
  ceres::AutoDiffManifold<EuclideanFunctor, 3, 3> manifold;
  int tangent_size = manifold.TangentSize();
  (void)tangent_size;  // Không kiểm tra kết quả trả về
}
