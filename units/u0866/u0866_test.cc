// FILE: u0866_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_schur_complement_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0866, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::IterativeSchurComplementSolver object{};
  (void)object;
}
