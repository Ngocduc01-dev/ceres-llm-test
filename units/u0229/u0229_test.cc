// FILE: u0229_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"

#include <set>
#include <utility>
#include <vector>

namespace ceres {
namespace internal {

// P1: START -> END
TEST(BlockRandomAccessSparseMatrixDestructorTest, DestroyObject_P1) {
  std::vector<Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);

  std::set<std::pair<int, int>> block_pairs;
  block_pairs.insert(std::make_pair(0, 0));
  block_pairs.insert(std::make_pair(1, 1));

  {
    BlockRandomAccessSparseMatrix matrix(blocks, block_pairs, nullptr, 1);
  }  // destructor ~BlockRandomAccessSparseMatrix() được gọi tại đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
