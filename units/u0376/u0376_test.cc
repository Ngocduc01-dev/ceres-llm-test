// FILE: u0376_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END
TEST(PartitionedMatrixViewNumColsF, TC1_ReturnNumColsF) {
  // Cấu trúc khối: 1 hàng khối (cỡ 2), 2 khối cột (cỡ 2 mỗi khối).
  auto* bs = new CompressedRowBlockStructure;

  Block col_e;
  col_e.size = 2;
  col_e.position = 0;
  bs->cols.push_back(col_e);

  Block col_f;
  col_f.size = 2;
  col_f.position = 2;
  bs->cols.push_back(col_f);

  CompressedRow row;
  row.block.size = 2;
  row.block.position = 0;

  Cell cell_e;
  cell_e.block_id = 0;
  cell_e.position = 0;
  row.cells.push_back(cell_e);

  Cell cell_f;
  cell_f.block_id = 1;
  cell_f.position = 4;
  row.cells.push_back(cell_f);

  bs->rows.push_back(row);

  // BlockSparseMatrix nhận quyền sở hữu bs.
  BlockSparseMatrix matrix(bs);

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);

  PartitionedMatrixView<2, 2, 2> view(options, matrix);
  view.num_cols_f();
}

}  // namespace internal
}  // namespace ceres
