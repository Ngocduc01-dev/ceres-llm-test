// FILE: u1104_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END
TEST(CreateTransposeTest, TC1_CallsTarget) {
  CompressedRowBlockStructure & bs a0{};
  ceres::internal::CreateTranspose(a0);
}

// P2: START -> 1 -> END
TEST(CreateTransposeTest, TC2_CallsTarget) {
  CompressedRowBlockStructure & bs a0{};
  ceres::internal::CreateTranspose(a0);
}

// P3: START -> 1 -> END
TEST(CreateTransposeTest, TC3_CallsTarget) {
  CompressedRowBlockStructure & bs a0{};
  ceres::internal::CreateTranspose(a0);
}

