// FILE: u0274_test.cc
#include "gtest/gtest.h"
#include "ceres/coordinate_descent_minimizer.h"

TEST(Unit_u0274, PathP1) {
  // Path P1: START -> 1 -> END.
  // Scope exit invokes ~CoordinateDescentMinimizer().
  ceres::internal::CoordinateDescentMinimizer object(nullptr);
}
