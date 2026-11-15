// FILE: u0950_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0950, TC1_CallsTarget) {
  int new_num_rows{};
  int new_num_cols{};
  ceres::internal::TripletSparseMatrix object{};
  object.Resize(new_num_rows, new_num_cols);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0950, TC2_CallsTarget) {
  int new_num_rows{};
  int new_num_cols{};
  ceres::internal::TripletSparseMatrix object{};
  object.Resize(new_num_rows, new_num_cols);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0950, TC3_CallsTarget) {
  int new_num_rows{};
  int new_num_cols{};
  ceres::internal::TripletSparseMatrix object{};
  object.Resize(new_num_rows, new_num_cols);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0950, TC4_CallsTarget) {
  int new_num_rows{};
  int new_num_cols{};
  ceres::internal::TripletSparseMatrix object{};
  object.Resize(new_num_rows, new_num_cols);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0950, TC5_CallsTarget) {
  int new_num_rows{};
  int new_num_cols{};
  ceres::internal::TripletSparseMatrix object{};
  object.Resize(new_num_rows, new_num_cols);
}
