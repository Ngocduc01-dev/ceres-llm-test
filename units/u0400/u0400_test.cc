// FILE: u0400_test.cc
#include "gtest/gtest.h"
#include "ceres/program_evaluator.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0400, PathP1) {
  int arg_0 = 1;
  int arg_1 = 1;
  int arg_2 = 1;
  int arg_3 = 1;
  ceres::internal::ProgramEvaluator::EvaluateScratch target(arg_0, arg_1, arg_2, arg_3);
  target.Init(1, 1.0, 1, 1);
}
