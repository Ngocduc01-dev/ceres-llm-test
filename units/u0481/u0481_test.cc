// FILE: u0481_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0481, PathP1) {
  int arg_0 = 1;
  ceres::internal::ParameterBlock target(arg_0);
  target.LowerBound(1);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0481, PathP2) {
  int arg_0 = 1;
  ceres::internal::ParameterBlock target(arg_0);
  target.LowerBound(1);
}
