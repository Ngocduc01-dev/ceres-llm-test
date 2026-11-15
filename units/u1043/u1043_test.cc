// FILE: u1043_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(ParameterBlocksToStateVectorTest, TC1_CallsTarget) {
  Program object{};
  double a0[5] = {};
  object.ParameterBlocksToStateVector(a0);
}

// P2: START -> 1 -> END
TEST(ParameterBlocksToStateVectorTest, TC2_CallsTarget) {
  Program object{};
  double a0[5] = {};
  object.ParameterBlocksToStateVector(a0);
}

