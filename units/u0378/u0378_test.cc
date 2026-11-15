// FILE: u0378_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(PartitionedMatrixViewFColsPartition, ReturnsFColsPartition) {
  // Ma trận khối: 1 hàng khối (kích thước 2), 2 khối cột (mỗi khối kích thước 2).
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.push_back(Block(2, 0));
  bs->cols.push_back(Block(2, 2));

  CompressedRow row;
  row.block = Block(2, 0);
  row.cells.push_back(Cell(0, 0));  // khối E
  row.cells.push_back(Cell(1, 2));  // khối F
  bs->rows.push_back(row);

  BlockSparseMatrix matrix(bs);  // matrix sở hữu bs

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);  // 1 khối cột thuộc phần E

  PartitionedMatrixView<2, 2, 2> view(options, matrix);

  // Gọi unit một lần, không kiểm tra kết quả trả về.
  const std::vector<int>& f_cols = view.f_cols_partition();
  (void)f_cols;
}

}  // namespace internal
}  // namespace ceres
