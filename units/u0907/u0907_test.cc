// FILE: u0907_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/coordinate_descent_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0907, TC1_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer object{};
  (void)object;
}
