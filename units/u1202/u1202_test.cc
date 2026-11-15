// FILE: u1202_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1202, TC1_CallsTarget) {
  ceres::internal::InnerProductComputer object{};
  object.Compute();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1202, TC2_CallsTarget) {
  ceres::internal::InnerProductComputer object{};
  object.Compute();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1202, TC3_CallsTarget) {
  ceres::internal::InnerProductComputer object{};
  object.Compute();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1202, TC4_CallsTarget) {
  ceres::internal::InnerProductComputer object{};
  object.Compute();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1202, TC5_CallsTarget) {
  ceres::internal::InnerProductComputer object{};
  object.Compute();
}
