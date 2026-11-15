// FILE: u1008_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1008, TC1_CallsTarget) {
  ceres::internal::TypedLinearSolver object{};
  object.Statistics();
}
