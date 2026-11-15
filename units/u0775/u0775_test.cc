// FILE: u0775_test.cc
#include "gtest/gtest.h"
#include "ceres/visibility.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0775, TC1_CallsTarget) {
  CompressedRowBlockStructure block_structure{};
  const int num_eliminate_blocks{};
  ceres::internal::ComputeVisibility(block_structure, num_eliminate_blocks, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0775, TC2_CallsTarget) {
  CompressedRowBlockStructure block_structure{};
  const int num_eliminate_blocks{};
  ceres::internal::ComputeVisibility(block_structure, num_eliminate_blocks, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0775, TC3_CallsTarget) {
  CompressedRowBlockStructure block_structure{};
  const int num_eliminate_blocks{};
  ceres::internal::ComputeVisibility(block_structure, num_eliminate_blocks, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0775, TC4_CallsTarget) {
  CompressedRowBlockStructure block_structure{};
  const int num_eliminate_blocks{};
  ceres::internal::ComputeVisibility(block_structure, num_eliminate_blocks, nullptr);
}
