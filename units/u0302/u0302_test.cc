// FILE: u0302_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_checking_cost_function.h"
#include <string>

// Path P1: START -> 1 -> END.
TEST(Unit_u0302, PathP1) {
  ceres::internal::GradientCheckingIterationCallback target;
  target.error_log();
}
