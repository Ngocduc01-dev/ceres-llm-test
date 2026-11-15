// FILE: u0417_test.cc
#include <random>

#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/subset_preconditioner.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (hàm không có điểm rẽ nhánh)
TEST(SubsetPreconditionerDestructorTest, TC1_P1_StartToEnd) {
  std::mt19937 prng(42);

  BlockSparseMatrix::RandomMatrixOptions matrix_options;
  matrix_options.num_row_blocks = 3;
  matrix_options.min_row_block_size = 2;
  matrix_options.max_row_block_size = 2;
  matrix_options.num_col_blocks = 3;
  matrix_options.min_col_block_size = 2;
  matrix_options.max_col_block_size = 2;
  matrix_options.block_density = 1.0;

  std::unique_ptr<BlockSparseMatrix> A =
      BlockSparseMatrix::CreateRandomMatrix(matrix_options, prng);

  Preconditioner::Options options;
  options.subset_preconditioner_start_row_block = 1;
  options.sparse_linear_algebra_library_type = EIGEN_SPARSE;

  // Tạo object trên heap rồi delete để gọi destructor đúng một lần.
  SubsetPreconditioner* preconditioner =
      new SubsetPreconditioner(options, *A);
  delete preconditioner;
}

}  // namespace internal
}  // namespace ceres
