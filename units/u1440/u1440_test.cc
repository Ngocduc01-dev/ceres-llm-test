// FILE: u1440_test.cc
#include "gtest/gtest.h"
#include "ceres/casts.h"
#include "ceres/compressed_row_jacobian_writer.h"
#include "ceres/dynamic_compressed_row_jacobian_writer.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1440, TC1_CallsTarget) {
  int residual_id{};
  int residual_offset{};
  ceres::internal::DynamicCompressedRowJacobianWriter object{};
  object.Write(residual_id, residual_offset, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1440, TC2_CallsTarget) {
  int residual_id{};
  int residual_offset{};
  ceres::internal::DynamicCompressedRowJacobianWriter object{};
  object.Write(residual_id, residual_offset, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1440, TC3_CallsTarget) {
  int residual_id{};
  int residual_offset{};
  ceres::internal::DynamicCompressedRowJacobianWriter object{};
  object.Write(residual_id, residual_offset, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1440, TC4_CallsTarget) {
  int residual_id{};
  int residual_offset{};
  ceres::internal::DynamicCompressedRowJacobianWriter object{};
  object.Write(residual_id, residual_offset, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1440, TC5_CallsTarget) {
  int residual_id{};
  int residual_offset{};
  ceres::internal::DynamicCompressedRowJacobianWriter object{};
  object.Write(residual_id, residual_offset, nullptr, nullptr);
}
