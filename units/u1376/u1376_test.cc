// FILE: u1376_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/solver.h"
#include "ceres/linear_solver.h"
#include "ceres/preconditioner.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1376, TC1_CallsTarget) {
  ceres::internal::(anonymous)::AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1376, TC2_CallsTarget) {
  ceres::internal::(anonymous)::AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1376, TC3_CallsTarget) {
  ceres::internal::(anonymous)::AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1376, TC4_CallsTarget) {
  ceres::internal::(anonymous)::AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(nullptr);
}
