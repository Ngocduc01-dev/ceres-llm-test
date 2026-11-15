// FILE: u1155_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(HasParameterBlockTest, TC1_CallsTarget) {
  Problem object{};
  double a0[5] = {};
  object.HasParameterBlock(a0);
}

