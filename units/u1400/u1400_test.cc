// FILE: u1400_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1400_Test, TC1_CallsTarget) {
  ceres::internal::ParameterBlock target{};
  target.RemoveResidualBlock(nullptr);
}
