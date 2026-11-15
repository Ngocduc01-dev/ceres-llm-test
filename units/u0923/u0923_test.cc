// FILE: u0923_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_eliminator.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  SchurEliminatorBase object{};
  LinearSolver::Options & options a0{};
  object.Create(a0);
}

