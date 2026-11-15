// FILE: u0455_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_cost_function.h"

namespace {
struct CostFunctor {
  bool operator()(const double* parameters, double* residuals) const {
    residuals[0] = parameters[0] * parameters[0];
    return true;
  }
};
}  // namespace

TEST(Unit_u0455, ReleasesNonOwnedFunctor) {
  CostFunctor functor;
  {
    ceres::NumericDiffCostFunction<CostFunctor, ceres::CENTRAL, 1, 1> target(
        &functor, ceres::DO_NOT_TAKE_OWNERSHIP);
    double value = 2.0;
    double* parameters[] = {&value};
    double residuals[1] = {};
    double jacobian[1] = {};
    double* jacobians[] = {jacobian};
    EXPECT_TRUE(target.Evaluate(parameters, residuals, jacobians));
    EXPECT_DOUBLE_EQ(residuals[0], 4.0);
    EXPECT_NEAR(jacobian[0], 4.0, 1e-6);
  }
}
