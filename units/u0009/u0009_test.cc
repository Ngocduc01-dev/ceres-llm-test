// FILE: u0009_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace ceres {
namespace {

// Functor đơn giản cho AutoDiffManifold: Plus và Minus dạng cộng/trừ từng phần tử.
struct PlusMinusFunctor {
  template <typename T>
  bool Plus(const T* x, const T* delta, T* x_plus_delta) const {
    x_plus_delta[0] = x[0] + delta[0];
    x_plus_delta[1] = x[1] + delta[1];
    return true;
  }

  template <typename T>
  bool Minus(const T* y, const T* x, T* y_minus_x) const {
    y_minus_x[0] = y[0] - x[0];
    y_minus_x[1] = y[1] - x[1];
    return true;
  }
};

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AutoDiffManifoldFunctorTest, TC1_P1_ReturnFunctorReference) {
  AutoDiffManifold<PlusMinusFunctor, 2, 2> manifold;
  const PlusMinusFunctor& f = manifold.functor();
  (void)f;
}

}  // namespace
}  // namespace ceres
