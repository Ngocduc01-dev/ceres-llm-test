// FILE: u0219_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> END (destructor không có điểm rẽ nhánh)
TEST(BlockSparseJacobiPreconditionerDestructorTest, P1_StartToEnd) {
  // Cấu trúc khối: 1 row block (size 1), 1 col block (size 1), 1 cell.
  auto* bs = new CompressedRowBlockStructure;

  Block col;
  col.size = 1;
  col.position = 0;
  bs->cols.push_back(col);

  CompressedRow row;
  row.block.size = 1;
  row.block.position = 0;
  Cell cell;
  cell.block_id = 0;
  cell.position = 0;
  row.cells.push_back(cell);
  bs->rows.push_back(row);

  // BlockSparseMatrix nhận quyền sở hữu bs.
  BlockSparseMatrix A(bs);
  A.SetZero();

  Preconditioner::Options options;

  {
    BlockSparseJacobiPreconditioner preconditioner(options, A);
  }  // destructor được gọi tại đây (node START -> END)
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
