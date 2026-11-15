// FILE: u1493_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/evaluator.h"
#include "ceres/linear_solver.h"
#include "ceres/minimizer.h"
#include "ceres/program.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END
TEST(u1493_Test, TC1_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer target{};
  target.Solve(nullptr, nullptr, nullptr, nullptr);
}
