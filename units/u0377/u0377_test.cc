// FILE: u0377_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(PartitionedMatrixViewETest, ECColsPartitionP1) {
  // Cấu trúc khối: 1 khối hàng (cỡ 2), 2 khối cột (mỗi khối cỡ 2).
  auto* bs = new CompressedRowBlockStructure;

  bs->cols.emplace_back();
  bs->cols[0].size = 2;
  bs->cols[0].position = 0;
  bs->cols.emplace_back();
  bs->cols[1].size = 2;
  bs->cols[1].position = 2;

  bs->rows.emplace_back();
  CompressedRow& row = bs->rows[0];
  row.block.size = 2;
  row.block.position = 0;
  row.cells.emplace_back(0, 0);  // cell thuộc khối E (khối cột 0)
  row.cells.emplace_back(1, 4);  // cell thuộc khối F (khối cột 1)

  BlockSparseMatrix matrix(bs);

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);

  PartitionedMatrixView<2> view(options, matrix);

  // Gọi unit một lần, không kiểm tra kết quả trả về.
  const std::vector<int>& partition = view.e_cols_partition();
  (void)partition;
}

}  // namespace internal
}  // namespace ceres
