// FILE: u0791_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/program.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0791, TC1_CallsTarget) {
  ParameterBlockOrdering parameter_block_ordering{};
  ceres::internal::ReorderSchurComplementColumnsUsingSuiteSparse(parameter_block_ordering, nullptr);
}
