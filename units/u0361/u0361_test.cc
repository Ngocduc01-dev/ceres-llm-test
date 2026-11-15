// FILE: u0361_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockSetConstantTest, TC1_SetConstantPathP1) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock parameter_block(values, 3, 2);
  parameter_block.SetConstant();
}

}  // namespace internal
}  // namespace ceres
