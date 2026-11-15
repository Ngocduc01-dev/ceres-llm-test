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
