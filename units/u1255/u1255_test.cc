// FILE: u1255_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/schur_jacobi_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1255, TC1_CallsTarget) {
  ceres::internal::SchurJacobiPreconditioner object{};
  object.num_rows();
}
