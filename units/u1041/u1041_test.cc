// FILE: u1041_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(ParameterBlockSizeTest, TC1_CallsTarget) {
  ProblemImpl object{};
  double a0[5] = {};
  object.ParameterBlockSize(a0);
}

