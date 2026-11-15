// FILE: u0001_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"

namespace {

struct SimpleFunctor {
  template <typename T>
  bool operator()(const T* const x, T* residual) const {
    residual[0] = x[0];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AutoDiffCostFunctionFunctorTest, TC1_ReturnsFunctorReference) {
  SimpleFunctor functor;
  ceres::AutoDiffCostFunction<SimpleFunctor, 1, 1> cost_function(
      &functor, ceres::DO_NOT_TAKE_OWNERSHIP);
  const SimpleFunctor& result = cost_function.functor();
  (void)result;
}
