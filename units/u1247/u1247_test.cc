// FILE: u1247_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END
TEST(ToStringTest, TC1_CallsTarget) {
  ParameterBlock object{};
  object.ToString();
}

