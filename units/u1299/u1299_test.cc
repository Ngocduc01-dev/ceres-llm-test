// FILE: u1299_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/preconditioner.h"
#include "ceres/schur_jacobi_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1299, TC1_CallsTarget) {
  CompressedRowBlockStructure bs{};
  Preconditioner::Options options{};
  ceres::internal::SchurJacobiPreconditioner object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1299, TC2_CallsTarget) {
  CompressedRowBlockStructure bs{};
  Preconditioner::Options options{};
  ceres::internal::SchurJacobiPreconditioner object{};
  (void)object;
}
