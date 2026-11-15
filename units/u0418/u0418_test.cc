// FILE: u0418_test.cc
#include "gtest/gtest.h"
#include "ceres/subset_preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SubsetPreconditionerNumRows, TC1_ReturnNumCols) {
  // Ma trận khối 1x1: 1 hàng khối, 1 cột khối, 1 cell.
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.push_back(Block(1, 0));

  bs->rows.push_back(CompressedRow());
  CompressedRow& row = bs->rows.back();
  row.block = Block(1, 0);
  row.cells.push_back(Cell(0, 0));

  BlockSparseMatrix A(bs);  // A lấy quyền sở hữu bs
  A.SetZero();

  Preconditioner::Options options;
  options.type = SUBSET;
  options.sparse_linear_algebra_library_type = EIGEN_SPARSE;
  options.subset_preconditioner_start_row_block = 0;

  SubsetPreconditioner preconditioner(options, A);
  preconditioner.num_rows();  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
