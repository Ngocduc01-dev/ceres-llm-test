// FILE: u1354_test.cc
#include "gtest/gtest.h"
#include "ceres/casts.h"
#include "ceres/dense_jacobian_writer.h"
#include "ceres/dense_sparse_matrix.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1354, TC1_CallsTarget) {
  int residual_id{};
  int residual_offset{};
  ceres::internal::DenseJacobianWriter object{};
  object.Write(residual_id, residual_offset, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1354, TC2_CallsTarget) {
  int residual_id{};
  int residual_offset{};
  ceres::internal::DenseJacobianWriter object{};
  object.Write(residual_id, residual_offset, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1354, TC3_CallsTarget) {
  int residual_id{};
  int residual_offset{};
  ceres::internal::DenseJacobianWriter object{};
  object.Write(residual_id, residual_offset, nullptr, nullptr);
}
