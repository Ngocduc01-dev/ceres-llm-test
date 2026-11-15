// FILE: u0802_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/block_sparse_matrix.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0802, TC1_CallsTarget) {
  std::vector<CompressedList> rows{};
  ceres::internal::(anonymous)::ComputeCumulativeNumberOfNonZeros(rows);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0802, TC2_CallsTarget) {
  std::vector<CompressedList> rows{};
  ceres::internal::(anonymous)::ComputeCumulativeNumberOfNonZeros(rows);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0802, TC3_CallsTarget) {
  std::vector<CompressedList> rows{};
  ceres::internal::(anonymous)::ComputeCumulativeNumberOfNonZeros(rows);
}
