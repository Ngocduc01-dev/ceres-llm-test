// FILE: u0226_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> END (destructor không có nhánh)
TEST(BlockRandomAccessDiagonalMatrixDestructorTest, DestroyObject) {
  std::vector<Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);

  // Object được tạo trên heap rồi huỷ tường minh để gọi destructor đúng một lần.
  BlockRandomAccessDiagonalMatrix* matrix =
      new BlockRandomAccessDiagonalMatrix(blocks, nullptr, 1);
  delete matrix;
}

}  // namespace internal
}  // namespace ceres
