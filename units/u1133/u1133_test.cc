// FILE: u1133_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(InitStorageTest, TC1_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  CompressedRowBlockStructure & bs a0{};
  object.InitStorage(a0);
}

