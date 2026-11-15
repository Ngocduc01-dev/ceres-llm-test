// FILE: u1301_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1301_Test, TC1_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.Init(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1301_Test, TC2_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.Init(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1301_Test, TC3_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.Init(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1301_Test, TC4_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.Init(nullptr, nullptr, nullptr, nullptr);
}
