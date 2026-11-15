// FILE: u0794_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END
TEST(set_lhsTest, TC1_CallsTarget) {
  SchurComplementSolver object{};
  std::unique_ptr<BlockRandomAccessMatrix> a0{};
  object.set_lhs(a0);
}

