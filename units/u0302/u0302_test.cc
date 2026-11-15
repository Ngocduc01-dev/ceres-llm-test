// FILE: u0302_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_checking_cost_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0302, PathP1) {
  ceres::internal::GradientCheckingIterationCallback target;
  target.error_log();
}
