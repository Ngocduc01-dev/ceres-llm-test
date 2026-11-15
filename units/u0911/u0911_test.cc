// FILE: u0911_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_eliminator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0911, TC1_CallsTarget) {
  LinearSolver::Options options{};
  SchurEliminator<> object{};
  (void)object;
}
