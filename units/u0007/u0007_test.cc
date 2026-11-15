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
