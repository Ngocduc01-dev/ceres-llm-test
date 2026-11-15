// FILE: u0224_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có nhánh rẽ)
TEST(BlockRandomAccessDenseMatrixValuesTest, P1_ReturnValuesPointer) {
  std::vector<Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(1, 2);

  BlockRandomAccessDenseMatrix matrix(blocks, nullptr, 1);

  const double* result = matrix.values();
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
