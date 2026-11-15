// FILE: u0418_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/subset_preconditioner.h"

TEST(Unit_u0418, NumRows) {
  if (!ceres::IsSparseLinearAlgebraLibraryTypeAvailable(ceres::EIGEN_SPARSE)) {
    GTEST_SKIP() << "Eigen sparse support is unavailable";
  }
  auto* structure = new ceres::internal::CompressedRowBlockStructure;
  structure->cols.emplace_back(3, 0);
  ceres::internal::BlockSparseMatrix matrix(structure);

  ceres::Preconditioner::Options options;
  options.subset_preconditioner_start_row_block = 0;
  options.sparse_linear_algebra_library_type = ceres::EIGEN_SPARSE;
  ceres::internal::SubsetPreconditioner target(options, matrix);

  EXPECT_EQ(target.num_rows(), 3);
}
