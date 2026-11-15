// FILE: u0375_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END
TEST(PartitionedMatrixViewNumColsE, TC1_ReturnNumColsE) {
  // Ma trận 1x2: 1 khối hàng, 2 khối cột (mỗi khối cỡ 1).
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.push_back(Block(1, 0));  // khối cột E
  bs->cols.push_back(Block(1, 1));  // khối cột F

  bs->rows.resize(1);
  CompressedRow& row = bs->rows[0];
  row.block = Block(1, 0);
  row.cells.push_back(Cell(0, 0));  // ô thuộc E
  row.cells.push_back(Cell(1, 1));  // ô thuộc F

  BlockSparseMatrix matrix(bs);  // matrix sở hữu bs

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);

  PartitionedMatrixView<Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic> view(
      options, matrix);

  view.num_cols_e();  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
