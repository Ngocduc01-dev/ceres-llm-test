// FILE: u0354_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0354, PathP1) {
  int arg_0 = 1;
  ceres::internal::BlockUntilFinished target(arg_0);
  target.BlockUntilFinished(1);
}
