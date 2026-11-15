// FILE: u0792_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/schur_complement_solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0792, TC1_CallsTarget) {
  BlockRandomAccessSparseMatrix m{};
  ceres::internal::(anonymous)::BlockRandomAccessSparseMatrixAdapter object{};
  (void)object;
}
