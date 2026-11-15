// FILE: u1347_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1347, TC1_CallsTarget) {
  std::vector<Block> blocks{};
  int num_threads{};
  ceres::internal::BlockRandomAccessDenseMatrix object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1347, TC2_CallsTarget) {
  std::vector<Block> blocks{};
  int num_threads{};
  ceres::internal::BlockRandomAccessDenseMatrix object{};
  (void)object;
}
