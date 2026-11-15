// FILE: u0465_test.cc
#include "gtest/gtest.h"
#include "ceres/conditioned_cost_function.h"

namespace {
class IdentityCostFunction final : public ceres::SizedCostFunction<1, 1> {
 public:
  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** /*jacobians*/) const override {
    residuals[0] = parameters[0][0];
    return true;
  }
};
}  // namespace

TEST(Unit_u0465, DeletesOwnedWrappedFunctions) {
  std::vector<ceres::CostFunction*> conditioners;
  conditioners.push_back(new IdentityCostFunction);
  ceres::ConditionedCostFunction target(new IdentityCostFunction,
                                         conditioners,
                                         ceres::TAKE_OWNERSHIP);
  double value = 2.0;
  double* parameters[] = {&value};
  double residuals[1] = {};
  EXPECT_TRUE(target.Evaluate(parameters, residuals, nullptr));
  EXPECT_DOUBLE_EQ(residuals[0], 2.0);
}
