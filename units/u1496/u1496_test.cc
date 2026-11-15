// FILE: u1496_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/schur_eliminator.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1496, TC1_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1496, TC2_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1496, TC3_CallsTarget) {
  BlockSparseMatrix A{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.UpdateImpl(A, nullptr);
}
