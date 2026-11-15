// FILE: u0775_test.cc
#include "gtest/gtest.h"
#include "ceres/visibility.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(ComputeVisibilityTest, TC1_CallsTarget) {
  CompressedRowBlockStructure & block_structure a0{};
  int a1 = 0;
  int a2[5] = {};
  ceres::internal::ComputeVisibility(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(ComputeVisibilityTest, TC2_CallsTarget) {
  CompressedRowBlockStructure & block_structure a0{};
  int a1 = 0;
  int a2[5] = {};
  ceres::internal::ComputeVisibility(a0, a1, a2);
}

// P3: START -> 1 -> END
TEST(ComputeVisibilityTest, TC3_CallsTarget) {
  CompressedRowBlockStructure & block_structure a0{};
  int a1 = 0;
  int a2[5] = {};
  ceres::internal::ComputeVisibility(a0, a1, a2);
}

