// FILE: u0174_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> END
TEST(CauchyLossConstructorTest, P1_SingleStraightPath) {
  ceres::CauchyLoss loss(2.0);
}
