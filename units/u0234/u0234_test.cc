// FILE: u0234_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có nhánh rẽ)
TEST(BlockSparseMatrixMutableValuesTest, P1_ReturnValues) {
  auto* block_structure = new CompressedRowBlockStructure;
  block_structure->cols.push_back(Block(2, 0));

  CompressedRow row;
  row.block = Block(2, 0);
  row.cells.push_back(Cell(0, 0));
  block_structure->rows.push_back(row);

  BlockSparseMatrix matrix(block_structure, false);
  double* values = matrix.mutable_values();
  (void)values;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
