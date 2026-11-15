// FILE: u0443_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_autodiff_cost_function.h"

namespace {
struct CostFunctor {
  template <typename T>
  bool operator()(T const* const* parameters, T* residuals) const {
    residuals[0] = parameters[0][0] * parameters[0][0];
    return true;
  }
};
}  // namespace

TEST(Unit_u0443, ReleasesNonOwnedFunctor) {
  CostFunctor functor;
  {
    ceres::DynamicAutoDiffCostFunction<CostFunctor> target(
        &functor, ceres::DO_NOT_TAKE_OWNERSHIP);
    target.AddParameterBlock(1);
    target.SetNumResiduals(1);
    double value = 2.0;
    double* parameters[] = {&value};
    double residuals[1] = {};
    EXPECT_TRUE(target.Evaluate(parameters, residuals, nullptr));
    EXPECT_DOUBLE_EQ(residuals[0], 4.0);
  }
}
