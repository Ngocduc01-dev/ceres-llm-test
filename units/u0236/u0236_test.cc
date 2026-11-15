// FILE: u0236_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockSparseMatrixDataValuesTest, P1_ReturnValuesPointer) {
  CompressedRowBlockStructure block_structure;
  const double values[3] = {3.5, -7.25, 0.5};

  BlockSparseMatrixData data(&block_structure, values);
  const double* result = data.values();
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
