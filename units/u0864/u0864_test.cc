// FILE: u0864_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0864, TC1_CallsTarget) {
  ceres::internal::InnerProductComputer object{};
  object.mutable_result();
}
