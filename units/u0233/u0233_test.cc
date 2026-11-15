// FILE: u0233_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockSparseMatrixValuesTest, P1_ReturnValuesPointer) {
  auto* bs = new CompressedRowBlockStructure;

  // 1 cột khối kích thước 2, bắt đầu ở vị trí 0.
  bs->cols.push_back(Block(2, 0));

  // 1 hàng khối kích thước 1, vị trí 0, có 1 cell trỏ tới cột khối 0.
  bs->rows.push_back(CompressedRow());
  bs->rows[0].block = Block(1, 0);
  bs->rows[0].cells.push_back(Cell(0, 0));

  // Matrix nhận quyền sở hữu block structure.
  BlockSparseMatrix matrix(bs, false);

  const double* p = matrix.values();
  (void)p;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
