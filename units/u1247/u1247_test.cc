// FILE: u1247_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1247, TC1_CallsTarget) {
  ceres::internal::ParameterBlock object{};
  object.ToString();
}
