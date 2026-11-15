// FILE: u0004_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace ceres {
namespace {

// Functor Euclidean đơn giản dùng làm tham số template cho AutoDiffManifold.
struct TestEuclideanFunctor {
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

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AutoDiffManifoldConstructorTest, TC1_DefaultConstructor) {
  AutoDiffManifold<TestEuclideanFunctor, 3, 3> manifold;
  (void)manifold;
}

}  // namespace
}  // namespace ceres
