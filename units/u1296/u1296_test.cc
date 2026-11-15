// FILE: u1296_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1296, TC1_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.LeftMultiplyAndAccumulateE(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1296, TC2_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.LeftMultiplyAndAccumulateE(nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1296, TC3_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.LeftMultiplyAndAccumulateE(nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1296, TC4_CallsTarget) {
  ceres::internal::PartitionedMatrixView object{};
  object.LeftMultiplyAndAccumulateE(nullptr, nullptr);
}
