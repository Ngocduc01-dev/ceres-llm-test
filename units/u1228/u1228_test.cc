// FILE: u1228_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/triplet_sparse_matrix.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1228, TC1_CallsTarget) {
  TripletSparseMatrix block_jacobian_transpose{};
  ceres::internal::(anonymous)::CreateBlockJacobian(block_jacobian_transpose);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1228, TC2_CallsTarget) {
  TripletSparseMatrix block_jacobian_transpose{};
  ceres::internal::(anonymous)::CreateBlockJacobian(block_jacobian_transpose);
}
