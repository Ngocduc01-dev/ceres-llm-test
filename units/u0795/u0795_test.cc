// FILE: u0795_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END
TEST(lhsTest, TC1_CallsTarget) {
  SchurComplementSolver object{};
  object.lhs();
}

