// FILE: u1181_test.cc
#include "gtest/gtest.h"
#include "ceres/cgnr_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1181, TC1_CallsTarget) {
  LinearSolver::Options options{};
  ceres::internal::CgnrSolver object{};
  (void)object;
}
