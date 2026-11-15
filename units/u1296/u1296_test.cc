// FILE: u1296_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"

// P1: START -> 1 -> END
TEST(u1296_Test, TC1_CallsTarget) {
  PartitionedMatrixView<> target{};
  target.LeftMultiplyAndAccumulateE(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1296_Test, TC2_CallsTarget) {
  PartitionedMatrixView<> target{};
  target.LeftMultiplyAndAccumulateE(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1296_Test, TC3_CallsTarget) {
  PartitionedMatrixView<> target{};
  target.LeftMultiplyAndAccumulateE(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1296_Test, TC4_CallsTarget) {
  PartitionedMatrixView<> target{};
  target.LeftMultiplyAndAccumulateE(nullptr, nullptr);
}
