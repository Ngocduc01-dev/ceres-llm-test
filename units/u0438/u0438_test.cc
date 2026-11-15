// FILE: u0438_test.cc
#include <random>

#include "ceres/autodiff_manifold.h"
#include "gtest/gtest.h"

namespace ceres {
namespace {

// Functor Euclid kích thước N dùng cho AutoDiffManifold.
template <int N>
struct EuclideanFunctorN {
  template <typename T>
  bool operator()(const T* x, const T* delta, T* x_plus_delta) const {
    for (int i = 0; i < N; ++i) {
      x_plus_delta[i] = x[i] + delta[i];
    }
    return true;
  }

  template <typename T>
  bool Minus(const T* y, const T* x, T* y_minus_x) const {
    for (int i = 0; i < N; ++i) {
      y_minus_x[i] = y[i] - x[i];
    }
    return true;
  }
};

// Gọi MinusJacobian một lần với x ngẫu nhiên (seed cố định) trong [-1, 1].
template <int N>
void CallMinusJacobian() {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-1.0, 1.0);

  double x[N];
  for (int i = 0; i < N; ++i) {
    x[i] = dist(gen);
  }
  double jacobian[N * N];
  for (int i = 0; i < N * N; ++i) {
    jacobian[i] = 0.0;
  }

  AutoDiffManifold<EuclideanFunctorN<N>, N, N> manifold;
  manifold.MinusJacobian(x, jacobian);
}

// P2: node 2: đúng, rồi sai (1 lần lặp)
TEST(AutoDiffManifoldMinusJacobian, TC1_OneIteration) {
  CallMinusJacobian<1>();
}

// P3: node 2: đúng x2, rồi sai (2 lần lặp)
TEST(AutoDiffManifoldMinusJacobian, TC2_TwoIterations) {
  CallMinusJacobian<2>();
}

// P4: node 2: đúng x3, rồi sai (3 lần lặp)
TEST(AutoDiffManifoldMinusJacobian, TC3_ThreeIterations) {
  CallMinusJacobian<3>();
}

// P5: node 2: đúng x4, rồi sai (4 lần lặp)
TEST(AutoDiffManifoldMinusJacobian, TC4_FourIterations) {
  CallMinusJacobian<4>();
}

// P6: node 2: đúng x5, rồi sai (5 lần lặp)
TEST(AutoDiffManifoldMinusJacobian, TC5_FiveIterations) {
  CallMinusJacobian<5>();
}

}  // namespace
}  // namespace ceres
