// FILE: u0019_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_autodiff_cost_function.h"

namespace {

struct SimpleFunctor {
  template <typename T>
  bool operator()(T const* const* parameters, T* residuals) const {
    residuals[0] = parameters[0][0];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DynamicAutoDiffCostFunctionFunctorTest, ReturnsFunctorReference) {
  SimpleFunctor functor;
  ceres::DynamicAutoDiffCostFunction<SimpleFunctor> cost_function(
      &functor, ceres::DO_NOT_TAKE_OWNERSHIP);
  const SimpleFunctor& result = cost_function.functor();
  (void)result;
}
