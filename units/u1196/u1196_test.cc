// FILE: u1196_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1196, TC1_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.UpdateBlockDiagonalFtFSingleThreaded(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1196, TC2_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.UpdateBlockDiagonalFtFSingleThreaded(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1196, TC3_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.UpdateBlockDiagonalFtFSingleThreaded(nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1196, TC4_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.UpdateBlockDiagonalFtFSingleThreaded(nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1196, TC5_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.UpdateBlockDiagonalFtFSingleThreaded(nullptr);
}
