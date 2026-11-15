// FILE: u1487_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/linear_solver.h"
#include "ceres/minimizer.h"
#include "ceres/parallel_for.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1487_Test, TC1_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1487_Test, TC2_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1487_Test, TC3_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1487_Test, TC4_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}
