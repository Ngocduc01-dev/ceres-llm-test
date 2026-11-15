// FILE: u0452_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

TEST(Unit_u0452, ReleasesNonOwnedLoss) {
  ceres::TrivialLoss loss;
  {
    ceres::ScaledLoss target(&loss, 2.0, ceres::DO_NOT_TAKE_OWNERSHIP);
    double rho[3] = {};
    target.Evaluate(3.0, rho);
    EXPECT_DOUBLE_EQ(rho[0], 6.0);
  }
}
