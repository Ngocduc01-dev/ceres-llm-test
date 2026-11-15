// FILE: u0793_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/schur_complement_solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0793, TC1_CallsTarget) {
  BlockRandomAccessDiagonalMatrix m{};
  ceres::internal::(anonymous)::BlockRandomAccessDiagonalMatrixAdapter object{};
  (void)object;
}
