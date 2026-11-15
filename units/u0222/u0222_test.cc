// FILE: u0222_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockRandomAccessDenseMatrixNumRowsTest, P1_ReturnNumRows) {
  std::vector<Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);
  BlockRandomAccessDenseMatrix matrix(blocks, nullptr, 1);
  matrix.num_rows();
}

}  // namespace internal
}  // namespace ceres
