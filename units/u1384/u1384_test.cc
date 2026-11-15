// FILE: u1384_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END
TEST(u1384_Test, TC1_CallsTarget) {
  ceres::internal::ParameterBlock target{};
  target.EnableResidualBlockDependencies();
}
