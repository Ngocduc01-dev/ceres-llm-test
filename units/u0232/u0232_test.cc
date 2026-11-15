// FILE: u0232_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockSparseMatrixNumNonzerosTest, TC1_P1_ReturnNumNonzeros) {
  auto* block_structure = new CompressedRowBlockStructure;

  // Một khối cột kích thước 2, bắt đầu tại vị trí 0.
  block_structure->cols.push_back(Block(2, 0));

  // Một hàng khối kích thước 2, chứa một cell trỏ tới khối cột 0.
  CompressedRow row;
  row.block = Block(2, 0);
  row.cells.push_back(Cell(0, 0));
  block_structure->rows.push_back(row);

  // Constructor nhận quyền sở hữu block_structure.
  BlockSparseMatrix matrix(block_structure, false);

  // Không kiểm tra kết quả trả về, chỉ gọi hàm.
  matrix.num_nonzeros();
}

}  // namespace internal
}  // namespace ceres
