// FILE: u0223_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"

#include <vector>

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockRandomAccessDenseMatrixNumCols, ReturnsNumRows) {
  std::vector<Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);
  BlockRandomAccessDenseMatrix matrix(blocks, nullptr, 1);
  matrix.num_cols();
}

}  // namespace internal
}  // namespace ceres
