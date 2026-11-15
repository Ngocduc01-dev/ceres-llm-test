// FILE: u1423_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_compressed_row_jacobian_writer.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1423, TC1_CallsTarget) {
  ceres::internal::DynamicCompressedRowJacobianWriter object{};
  object.CreateJacobian();
}
