// FILE: u1229_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"
#include "ceres/casts.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1229, TC1_CallsTarget) {
  LinearSolver::PerSolveOptions arg0{};
  ceres::internal::DenseSchurComplementSolver object{};
  object.SolveReducedLinearSystem(arg0, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1229, TC2_CallsTarget) {
  LinearSolver::PerSolveOptions arg0{};
  ceres::internal::DenseSchurComplementSolver object{};
  object.SolveReducedLinearSystem(arg0, nullptr);
}
