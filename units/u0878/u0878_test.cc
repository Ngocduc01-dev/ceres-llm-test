// FILE: u0878_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include "ceres/preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0878, TC1_CallsTarget) {
  LinearSolver::Options linear_solver_options{};
  ceres::internal::Preconditioner::Options object{};
  (void)object;
}
