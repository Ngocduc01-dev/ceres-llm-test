// FILE: u1376_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/solver.h"
#include "ceres/linear_solver.h"
#include "ceres/preconditioner.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END
TEST(u1376_Test, TC1_CallsTarget) {
  AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(nullptr);
}

// P2: START -> 1 -> END
TEST(u1376_Test, TC2_CallsTarget) {
  AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(nullptr);
}

// P3: START -> 1 -> END
TEST(u1376_Test, TC3_CallsTarget) {
  AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(nullptr);
}

// P4: START -> 1 -> END
TEST(u1376_Test, TC4_CallsTarget) {
  AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(nullptr);
}
