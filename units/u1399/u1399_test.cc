// FILE: u1399_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1399_Test, TC1_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.IsOrderingValid(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1399_Test, TC2_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.IsOrderingValid(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1399_Test, TC3_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.IsOrderingValid(nullptr, nullptr, nullptr);
}
