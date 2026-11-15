// FILE: u0003_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_first_order_function.h"

namespace {

struct QuadraticFunctor {
  template <typename T>
  bool operator()(const T* const x, T* cost) const {
    cost[0] = x[0] * x[0] + x[1] * x[1];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AutoDiffFirstOrderFunctionFunctorTest, P1_ReturnsFunctorReference) {
  ceres::AutoDiffFirstOrderFunction<QuadraticFunctor, 2> function(
      new QuadraticFunctor);
  const QuadraticFunctor& f = function.functor();
  (void)f;
}
