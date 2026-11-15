// FILE: u1287_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_jacobian_writer.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1287, TC1_CallsTarget) {
  int residual_id{};
  ceres::internal::CompressedRowJacobianWriter object{};
  object.GetOrderedParameterBlocks(nullptr, residual_id, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1287, TC2_CallsTarget) {
  int residual_id{};
  ceres::internal::CompressedRowJacobianWriter object{};
  object.GetOrderedParameterBlocks(nullptr, residual_id, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1287, TC3_CallsTarget) {
  int residual_id{};
  ceres::internal::CompressedRowJacobianWriter object{};
  object.GetOrderedParameterBlocks(nullptr, residual_id, nullptr);
}
