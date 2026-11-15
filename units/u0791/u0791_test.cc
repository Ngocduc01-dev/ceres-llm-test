// FILE: u0791_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/program.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END
TEST(ReorderSchurComplementColumnsUsingSuiteSparseTest, TC1_CallsTarget) {
  ParameterBlockOrdering & parameter_block_ordering a0{};
  ceres::internal::ReorderSchurComplementColumnsUsingSuiteSparse(a0, nullptr);
}

