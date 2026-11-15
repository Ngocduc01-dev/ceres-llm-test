// FILE: u0322_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0322, PathP1) {
  double arg_0 = 1.0;
  ceres::internal::LevenbergMarquardtStrategy target(arg_0);
  target.StepRejected(1.0);
}
