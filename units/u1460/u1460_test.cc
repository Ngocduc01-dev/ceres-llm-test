// FILE: u1460_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/ordered_groups.h"
#include "ceres/solver.h"
#include "ceres/linear_solver.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/reorder_program.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END
TEST(u1460_Test, TC1_CallsTarget) {
  SetupLinearSolver(nullptr);
}

// P2: START -> 1 -> END
TEST(u1460_Test, TC2_CallsTarget) {
  SetupLinearSolver(nullptr);
}

// P3: START -> 1 -> END
TEST(u1460_Test, TC3_CallsTarget) {
  SetupLinearSolver(nullptr);
}

// P4: START -> 1 -> END
TEST(u1460_Test, TC4_CallsTarget) {
  SetupLinearSolver(nullptr);
}
