// FILE: u0355_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0355, PathP1) {
  ceres::internal::BlockUntilFinished target;
  target.Block();
}
