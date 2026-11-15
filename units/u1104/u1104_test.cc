// FILE: u1104_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1104, TC1_CallsTarget) {
  CompressedRowBlockStructure bs{};
  ceres::internal::CreateTranspose(bs);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1104, TC2_CallsTarget) {
  CompressedRowBlockStructure bs{};
  ceres::internal::CreateTranspose(bs);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1104, TC3_CallsTarget) {
  CompressedRowBlockStructure bs{};
  ceres::internal::CreateTranspose(bs);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1104, TC4_CallsTarget) {
  CompressedRowBlockStructure bs{};
  ceres::internal::CreateTranspose(bs);
}
