// FILE: u1468_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1468_Test, TC1_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.CreateOrdering(nullptr);
}
