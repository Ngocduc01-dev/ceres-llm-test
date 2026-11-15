// FILE: u0372_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END
TEST(ParameterBlockMutableResidualBlocksTest, P1_ReturnsResidualBlocksPointer) {
  double values[3] = {1.0, 2.0, 3.0};
  ceres::internal::ParameterBlock block(values, 3, 2);
  ceres::internal::ParameterBlock::ResidualBlockSet* result =
      block.mutable_residual_blocks();
  (void)result;
}
