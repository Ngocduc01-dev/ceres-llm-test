// FILE: u0220_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> END (destructor không có nhánh)
TEST(BlockCRSJacobiPreconditionerDestructorTest, DestroyObject) {
  CompressedRowSparseMatrix A(2, 2, 4);
  A.mutable_row_blocks()->push_back(Block(2, 0));
  A.mutable_col_blocks()->push_back(Block(2, 0));

  Preconditioner::Options options;
  {
    BlockCRSJacobiPreconditioner preconditioner(options, A);
  }  // destructor được gọi tại đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
