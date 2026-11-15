// FILE: u1287_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_jacobian_writer.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1287_Test, TC1_CallsTarget) {
  ceres::internal::CompressedRowJacobianWriter target{};
  target.GetOrderedParameterBlocks(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1287_Test, TC2_CallsTarget) {
  ceres::internal::CompressedRowJacobianWriter target{};
  target.GetOrderedParameterBlocks(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1287_Test, TC3_CallsTarget) {
  ceres::internal::CompressedRowJacobianWriter target{};
  target.GetOrderedParameterBlocks(nullptr, nullptr, nullptr, nullptr);
}
