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

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1493, TC1_CallsTarget) {
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Solve(nullptr, nullptr, nullptr, nullptr);
}
