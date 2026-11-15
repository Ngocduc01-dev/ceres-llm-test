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
