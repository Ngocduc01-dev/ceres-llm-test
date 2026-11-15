// FILE: u0230_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END
TEST(BlockSparseMatrixNumRowsTest, P1_ReturnNumRows) {
  auto* block_structure = new CompressedRowBlockStructure;

  // 1 khối cột kích thước 2, bắt đầu tại vị trí 0.
  block_structure->cols.resize(1);
  block_structure->cols[0].size = 2;
  block_structure->cols[0].position = 0;

  // 1 hàng khối kích thước 2, có 1 cell trỏ tới khối cột 0.
  block_structure->rows.resize(1);
  block_structure->rows[0].block.size = 2;
  block_structure->rows[0].block.position = 0;
  block_structure->rows[0].cells.resize(1);
  block_structure->rows[0].cells[0].block_id = 0;
  block_structure->rows[0].cells[0].position = 0;

  // BlockSparseMatrix nhận quyền sở hữu block_structure.
  BlockSparseMatrix matrix(block_structure, false);

  matrix.num_rows();
}

}  // namespace internal
}  // namespace ceres
