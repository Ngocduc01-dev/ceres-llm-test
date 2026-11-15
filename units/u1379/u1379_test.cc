// FILE: u1379_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END
TEST(u1379_Test, TC1_CallsTarget) {
  ceres::internal::InnerProductComputer target{};
  target.ComputeOffsetsAndCreateResultMatrix(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1379_Test, TC2_CallsTarget) {
  ceres::internal::InnerProductComputer target{};
  target.ComputeOffsetsAndCreateResultMatrix(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1379_Test, TC3_CallsTarget) {
  ceres::internal::InnerProductComputer target{};
  target.ComputeOffsetsAndCreateResultMatrix(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1379_Test, TC4_CallsTarget) {
  ceres::internal::InnerProductComputer target{};
  target.ComputeOffsetsAndCreateResultMatrix(nullptr, nullptr);
}
