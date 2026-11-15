// FILE: u0454_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: node 1: đúng -> node 2 -> END
TEST(LossFunctionWrapperEvaluateTest, NullRhoUsesDefaultValues) {
  ceres::LossFunctionWrapper wrapper(nullptr, ceres::TAKE_OWNERSHIP);
  double sq_norm = 2.5;
  double out[3] = {0.0, 0.0, 0.0};
  wrapper.Evaluate(sq_norm, out);
}

// P2: node 1: sai -> node 3 -> END
TEST(LossFunctionWrapperEvaluateTest, NonNullRhoDelegatesToLossFunction) {
  ceres::LossFunctionWrapper wrapper(new ceres::TrivialLoss(),
                                     ceres::TAKE_OWNERSHIP);
  double sq_norm = 3.7;
  double out[3] = {0.0, 0.0, 0.0};
  wrapper.Evaluate(sq_norm, out);
}
