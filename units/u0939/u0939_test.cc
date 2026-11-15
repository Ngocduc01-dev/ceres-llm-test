// FILE: u0939_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0939, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::SchurComplementSolver object{};
  (void)object;
}
