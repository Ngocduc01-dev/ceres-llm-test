// FILE: u0802_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/block_sparse_matrix.cc"

// P1: START -> 1 -> END
TEST(ComputeCumulativeNumberOfNonZerosTest, TC1_CallsTarget) {
  std::vector<CompressedList> & rows a0{};
  ComputeCumulativeNumberOfNonZeros(a0);
}

// P2: START -> 1 -> END
TEST(ComputeCumulativeNumberOfNonZerosTest, TC2_CallsTarget) {
  std::vector<CompressedList> & rows a0{};
  ComputeCumulativeNumberOfNonZeros(a0);
}

// P3: START -> 1 -> END
TEST(ComputeCumulativeNumberOfNonZerosTest, TC3_CallsTarget) {
  std::vector<CompressedList> & rows a0{};
  ComputeCumulativeNumberOfNonZeros(a0);
}

