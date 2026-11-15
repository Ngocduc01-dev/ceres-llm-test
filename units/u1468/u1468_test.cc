// FILE: u1468_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1468, TC1_CallsTarget) {
  Program program{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.CreateOrdering(program);
}
