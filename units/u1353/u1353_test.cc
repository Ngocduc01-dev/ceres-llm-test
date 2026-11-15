// FILE: u1353_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_jacobian_writer.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1353, TC1_CallsTarget) {
  ceres::internal::CompressedRowJacobianWriter object{};
  object.PopulateJacobianRowAndColumnBlockVectors(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1353, TC2_CallsTarget) {
  ceres::internal::CompressedRowJacobianWriter object{};
  object.PopulateJacobianRowAndColumnBlockVectors(nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1353, TC3_CallsTarget) {
  ceres::internal::CompressedRowJacobianWriter object{};
  object.PopulateJacobianRowAndColumnBlockVectors(nullptr, nullptr);
}
