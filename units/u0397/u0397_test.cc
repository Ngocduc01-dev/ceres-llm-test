// FILE: u0397_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluation_callback.h"
#include "ceres/program.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0397, PathP1) {
  ceres::internal::Program target;
  target.mutable_evaluation_callback();
}
