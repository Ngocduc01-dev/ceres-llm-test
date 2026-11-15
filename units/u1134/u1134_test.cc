// FILE: u1134_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/ordered_groups.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END
TEST(CreateDefaultLinearSolverOrderingTest, TC1_CallsTarget) {
  Program & program a0{};
  CreateDefaultLinearSolverOrdering(a0);
}

// P2: START -> 1 -> END
TEST(CreateDefaultLinearSolverOrderingTest, TC2_CallsTarget) {
  Program & program a0{};
  CreateDefaultLinearSolverOrdering(a0);
}

