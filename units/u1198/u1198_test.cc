// FILE: u1198_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1198, TC1_CallsTarget) {
  const int num_rows{};
  const int num_cols{};
  std::vector<int> rows{};
  std::vector<int> cols{};
  std::vector<double> values{};
  ceres::internal::TripletSparseMatrix object{};
  (void)object;
}
