// FILE: u1134_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/ordered_groups.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1134, TC1_CallsTarget) {
  Program program{};
  ceres::internal::(anonymous)::CreateDefaultLinearSolverOrdering(program);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1134, TC2_CallsTarget) {
  Program program{};
  ceres::internal::(anonymous)::CreateDefaultLinearSolverOrdering(program);
}
