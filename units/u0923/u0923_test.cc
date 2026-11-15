// FILE: u0923_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_eliminator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0923, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::SchurEliminatorBase object{};
  object.Create(options);
}
