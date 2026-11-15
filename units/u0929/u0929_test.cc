// FILE: u0929_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0929, TC1_CallsTarget) {
  int num_threads{};
  ceres::internal::BlockSparseMatrix object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr, nullptr, num_threads);
}
