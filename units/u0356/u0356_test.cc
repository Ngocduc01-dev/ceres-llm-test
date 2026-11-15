// FILE: u0356_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0356, PathP1) {
  double * arg_0 = nullptr;
  int arg_1 = 1;
  int arg_2 = 1;
  ceres::internal::ParameterBlock target(arg_0, arg_1, arg_2);
  target.ParameterBlock(nullptr, 1, 1);
}
