// FILE: u1225_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END
TEST(AddDiagonalAndInvertTest, TC1_CallsTarget) {
  ImplicitSchurComplement object{};
  double a0[5] = {};
  object.AddDiagonalAndInvert(a0, nullptr);
}

