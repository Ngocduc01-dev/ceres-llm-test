// FILE: u0221_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"

#include <memory>
#include <vector>

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(BlockRandomAccessDenseMatrixDestructorTest, P1_StartToEnd) {
  std::vector<ceres::internal::Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);

  std::unique_ptr<ceres::internal::BlockRandomAccessDenseMatrix> matrix(
      new ceres::internal::BlockRandomAccessDenseMatrix(
          blocks, nullptr, 1));

  // Gọi destructor đúng một lần.
  matrix.reset();
}
