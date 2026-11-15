// FILE: u0231_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END
TEST(BlockSparseMatrixNumColsTest, P1_ReturnNumCols) {
  auto* block_structure = new CompressedRowBlockStructure;

  // Hai khối cột: kích thước 2 (vị trí 0) và 3 (vị trí 2).
  block_structure->cols.push_back(Block(2, 0));
  block_structure->cols.push_back(Block(3, 2));

  // Một khối hàng kích thước 1, có 2 cell trỏ tới 2 khối cột.
  block_structure->rows.emplace_back();
  CompressedRow& row = block_structure->rows.back();
  row.block = Block(1, 0);
  row.cells.push_back(Cell(0, 0));
  row.cells.push_back(Cell(1, 2));

  // Matrix nhận quyền sở hữu block_structure.
  BlockSparseMatrix matrix(block_structure, false);

  matrix.num_cols();
}

}  // namespace internal
}  // namespace ceres
