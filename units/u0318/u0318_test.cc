// FILE: u0318_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0318, PathP1) {
  const int arg_0 = 1;
  ceres::internal::DenseIterativeRefiner target(arg_0);
  target.DenseIterativeRefiner(1);
}
