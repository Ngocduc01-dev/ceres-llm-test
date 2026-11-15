// FILE: u1034_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END
TEST(IsConstantTest, TC1_CallsTarget) {
  ParameterBlock object{};
  object.IsConstant();
}

