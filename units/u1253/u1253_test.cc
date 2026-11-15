// FILE: u1253_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1253_Test, TC1_CallsTarget) {
  ceres::internal::ResidualBlock target{};
  target.ToString();
}
