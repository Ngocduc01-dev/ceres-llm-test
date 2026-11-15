// FILE: u1132_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END
TEST(InitStorageTest, TC1_CallsTarget) {
  DenseSchurComplementSolver object{};
  object.InitStorage(nullptr);
}

