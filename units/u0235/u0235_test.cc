// FILE: u0235_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockSparseMatrixDataBlockStructureTest, P1_ReturnsBlockStructure) {
  CompressedRowBlockStructure structure;
  double values[3] = {1.0, 2.0, 3.0};

  BlockSparseMatrixData data(&structure, values);
  const CompressedRowBlockStructure* result = data.block_structure();
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
