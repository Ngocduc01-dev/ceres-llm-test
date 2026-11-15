// FILE: u0316_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0316, PathP1) {
  const int arg_0 = 1;
  ceres::internal::SparseIterativeRefiner target(arg_0);
  target.SparseIterativeRefiner(1);
}
