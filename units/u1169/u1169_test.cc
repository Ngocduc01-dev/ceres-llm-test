// FILE: u1169_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1169, TC1_CallsTarget) {
  int num_threads{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr, nullptr, num_threads);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1169, TC2_CallsTarget) {
  int num_threads{};
  ceres::internal::CompressedRowSparseMatrix object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr, nullptr, num_threads);
}
