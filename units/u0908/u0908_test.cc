// FILE: u0908_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/implicit_schur_complement.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0908, TC1_CallsTarget) {
  ceres::internal::ImplicitSchurComplement object{};
  object.block_diagonal_FtF_inverse();
}
