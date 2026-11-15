// FILE: u0453_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

TEST(Unit_u0453, ReleasesNonOwnedLoss) {
  ceres::TrivialLoss loss;
  {
    ceres::LossFunctionWrapper target(&loss, ceres::DO_NOT_TAKE_OWNERSHIP);
    double rho[3] = {};
    target.Evaluate(3.0, rho);
    EXPECT_DOUBLE_EQ(rho[0], 3.0);
  }
}
