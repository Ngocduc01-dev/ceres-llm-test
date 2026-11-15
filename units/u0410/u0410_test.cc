// FILE: u0410_test.cc
#include "gtest/gtest.h"
#include "ceres/scratch_evaluate_preparer.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0410, PathP1) {
  int arg_0 = 1;
  ceres::internal::ScratchEvaluatePreparer target(arg_0);
  target.Init(1);
}
