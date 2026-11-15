// FILE: u0456_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_first_order_function.h"

namespace {
struct CostFunctor {
  bool operator()(const double* parameters, double* cost) const {
    *cost = parameters[0] * parameters[0];
    return true;
  }
};
}  // namespace

TEST(Unit_u0456, ReleasesNonOwnedFunctor) {
  CostFunctor functor;
  {
    ceres::NumericDiffFirstOrderFunction<CostFunctor, ceres::CENTRAL, 1> target(
        &functor, ceres::DO_NOT_TAKE_OWNERSHIP);
    const double parameters[1] = {2.0};
    double cost = 0.0;
    double gradient[1] = {};
    EXPECT_TRUE(target.Evaluate(parameters, &cost, gradient));
    EXPECT_DOUBLE_EQ(cost, 4.0);
    EXPECT_NEAR(gradient[0], 4.0, 1e-6);
  }
}
