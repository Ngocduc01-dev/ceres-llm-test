// FILE: u1442_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/ordered_groups.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1442_Test, TC1_CallsTarget) {
  ReorderProgramForSparseCholesky(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1442_Test, TC2_CallsTarget) {
  ReorderProgramForSparseCholesky(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1442_Test, TC3_CallsTarget) {
  ReorderProgramForSparseCholesky(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1442_Test, TC4_CallsTarget) {
  ReorderProgramForSparseCholesky(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
