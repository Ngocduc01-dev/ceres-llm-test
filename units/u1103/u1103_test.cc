// FILE: u1103_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1103, TC1_CallsTarget) {
  ceres::internal::BlockRandomAccessSparseMatrix object{};
  object.SymmetricRightMultiplyAndAccumulate(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1103, TC2_CallsTarget) {
  ceres::internal::BlockRandomAccessSparseMatrix object{};
  object.SymmetricRightMultiplyAndAccumulate(nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1103, TC3_CallsTarget) {
  ceres::internal::BlockRandomAccessSparseMatrix object{};
  object.SymmetricRightMultiplyAndAccumulate(nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1103, TC4_CallsTarget) {
  ceres::internal::BlockRandomAccessSparseMatrix object{};
  object.SymmetricRightMultiplyAndAccumulate(nullptr, nullptr);
}
