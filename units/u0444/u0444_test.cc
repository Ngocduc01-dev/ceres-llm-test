// FILE: u0444_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"

namespace {
struct CostFunctor {
  bool operator()(double const* const* parameters, double* residuals) const {
    residuals[0] = parameters[0][0] * parameters[0][0];
    return true;
  }
};
}  // namespace

TEST(Unit_u0444, ReleasesNonOwnedFunctor) {
  CostFunctor functor;
  {
    ceres::DynamicNumericDiffCostFunction<CostFunctor> target(
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
