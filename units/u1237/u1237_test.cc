// FILE: u1237_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/iterative_schur_complement_solver.h"
#include "ceres/power_series_expansion_preconditioner.h"
#include "ceres/preconditioner.h"
#include "ceres/schur_jacobi_preconditioner.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(CreatePreconditionerTest, TC1_CallsTarget) {
  IterativeSchurComplementSolver object{};
  object.CreatePreconditioner(nullptr);
}

// P2: START -> 1 -> END
TEST(CreatePreconditionerTest, TC2_CallsTarget) {
  IterativeSchurComplementSolver object{};
  object.CreatePreconditioner(nullptr);
}

