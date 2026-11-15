// FILE: u0374_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END
TEST(PartitionedMatrixViewNumColBlocksF, TC1_ReturnMember) {
  // Cấu trúc khối: 2 khối cột (kích thước 2, vị trí 0 và 2), 1 khối hàng (cao 2).
  auto* bs = new CompressedRowBlockStructure;

  bs->cols.resize(2);
  bs->cols[0].size = 2;
  bs->cols[0].position = 0;
  bs->cols[1].size = 2;
  bs->cols[1].position = 2;

  bs->rows.resize(1);
  bs->rows[0].block.size = 2;
  bs->rows[0].block.position = 0;
  bs->rows[0].cells.resize(2);
  bs->rows[0].cells[0].block_id = 0;
  bs->rows[0].cells[0].position = 0;
  bs->rows[0].cells[1].block_id = 1;
  bs->rows[0].cells[1].position = 4;

  // BlockSparseMatrix nhận quyền sở hữu bs.
  BlockSparseMatrix matrix(bs);

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);

  PartitionedMatrixView<Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic> view(
      options, matrix);

  view.num_col_blocks_f();  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
