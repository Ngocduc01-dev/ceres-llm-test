// FILE: u1237_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/iterative_schur_complement_solver.h"
#include "ceres/power_series_expansion_preconditioner.h"
#include "ceres/preconditioner.h"
#include "ceres/schur_jacobi_preconditioner.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1237, TC1_CallsTarget) {
  ceres::internal::IterativeSchurComplementSolver object{};
  object.CreatePreconditioner(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1237, TC2_CallsTarget) {
  ceres::internal::IterativeSchurComplementSolver object{};
  object.CreatePreconditioner(nullptr);
}
