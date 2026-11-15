// FILE: u1141_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END
TEST(InitStorageTest, TC1_CallsTarget) {
  SparseSchurComplementSolver object{};
  object.InitStorage(nullptr);
}

// P2: START -> 1 -> END
TEST(InitStorageTest, TC2_CallsTarget) {
  SparseSchurComplementSolver object{};
  object.InitStorage(nullptr);
}

// P3: START -> 1 -> END
TEST(InitStorageTest, TC3_CallsTarget) {
  SparseSchurComplementSolver object{};
  object.InitStorage(nullptr);
}

