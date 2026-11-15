// FILE: u1199_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1199, TC1_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.ToTripletSparseMatrix(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1199, TC2_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.ToTripletSparseMatrix(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1199, TC3_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.ToTripletSparseMatrix(nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1199, TC4_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.ToTripletSparseMatrix(nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1199, TC5_CallsTarget) {
  ceres::internal::BlockSparseMatrix object{};
  object.ToTripletSparseMatrix(nullptr);
}
