// FILE: u0301_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_checking_cost_function.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0301, PathP1) {
  ceres::internal::GradientCheckingIterationCallback target;
  target.gradient_error_detected();
}
