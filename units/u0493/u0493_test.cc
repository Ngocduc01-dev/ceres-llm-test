// FILE: u0493_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace ceres {
namespace {

// Manifold Euclid: Plus(x, delta) = x + delta
template <int N>
struct TestPlusFunctor {
  template <typename T>
  bool operator()(const T* x, const T* delta, T* x_plus_delta) const {
    for (int i = 0; i < N; ++i) {
      x_plus_delta[i] = x[i] + delta[i];
    }
    return true;
  }
};

// Path P1: node 2: đúng x1, sai; node 6: đúng x1, sai (N = 1)
TEST(AutoDiffManifoldPlusJacobian, TC1_N1) {
  AutoDiffManifold<TestPlusFunctor<1>, 1, 1> manifold(
      new TestPlusFunctor<1>());
  const double x[1] = {1.5};
  double jacobian[1] = {0.0};
  manifold.PlusJacobian(x, jacobian);
}

// Path P2: node 2: đúng x2, sai; node 6: đúng x2, sai (N = 2)
TEST(AutoDiffManifoldPlusJacobian, TC2_N2) {
  AutoDiffManifold<TestPlusFunctor<2>, 2, 2> manifold(
      new TestPlusFunctor<2>());
  const double x[2] = {-2.0, 0.5};
  double jacobian[4] = {0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}

// Path P3: node 2: đúng x3, sai; node 6: đúng x3, sai (N = 3)
TEST(AutoDiffManifoldPlusJacobian, TC3_N3) {
  AutoDiffManifold<TestPlusFunctor<3>, 3, 3> manifold(
      new TestPlusFunctor<3>());
  const double x[3] = {0.7, -1.3, 2.4};
  double jacobian[9] = {0.0};
  manifold.PlusJacobian(x, jacobian);
}

// Path P4: node 2: đúng x4, sai; node 6: đúng x4, sai (N = 4)
TEST(AutoDiffManifoldPlusJacobian, TC4_N4) {
  AutoDiffManifold<TestPlusFunctor<4>, 4, 4> manifold(
      new TestPlusFunctor<4>());
  const double x[4] = {3.1, -0.4, 1.2, -2.8};
  double jacobian[16] = {0.0};
  manifold.PlusJacobian(x, jacobian);
}

// Path P5: node 2: đúng x5, sai; node 6: đúng x5, sai (N = 5)
TEST(AutoDiffManifoldPlusJacobian, TC5_N5) {
  AutoDiffManifold<TestPlusFunctor<5>, 5, 5> manifold(
      new TestPlusFunctor<5>());
  const double x[5] = {0.3, 1.1, -4.2, 2.6, -0.9};
  double jacobian[25] = {0.0};
  manifold.PlusJacobian(x, jacobian);
}

}  // namespace
}  // namespace ceres
