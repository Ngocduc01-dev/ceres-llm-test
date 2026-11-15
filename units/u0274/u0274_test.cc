// FILE: u0274_test.cc
#include "gtest/gtest.h"
#include "ceres/coordinate_descent_minimizer.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0274, PathP1) {
  // Scope exit invokes ~CoordinateDescentMinimizer().
  ceres::internal::CoordinateDescentMinimizer object(nullptr);
}
