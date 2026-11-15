// FILE: u0419_test.cc
#include "gtest/gtest.h"
#include "ceres/subset_preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(SubsetPreconditionerNumCols, ReturnsNumCols) {
  // Ma trận khối thưa: 1 khối hàng (cỡ 1), 1 khối cột (cỡ 3), 1 cell.
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.emplace_back();
  bs->cols[0].size = 3;
  bs->cols[0].position = 0;

  bs->rows.emplace_back();
  CompressedRow& row = bs->rows[0];
  row.block.size = 1;
  row.block.position = 0;
  row.cells.emplace_back(0, 0);

  BlockSparseMatrix A(bs);  // A nhận quyền sở hữu bs

  Preconditioner::Options options;
  options.subset_preconditioner_start_row_block = 0;

  SubsetPreconditioner preconditioner(options, A);
  preconditioner.num_cols();  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
