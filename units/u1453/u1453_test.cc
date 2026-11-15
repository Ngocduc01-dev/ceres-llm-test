// FILE: u1453_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/triplet_sparse_matrix.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END
TEST(u1453_Test, TC1_CallsTarget) {
  ReorderSchurComplementColumnsUsingEigen(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1453_Test, TC2_CallsTarget) {
  ReorderSchurComplementColumnsUsingEigen(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1453_Test, TC3_CallsTarget) {
  ReorderSchurComplementColumnsUsingEigen(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1453_Test, TC4_CallsTarget) {
  ReorderSchurComplementColumnsUsingEigen(nullptr, nullptr, nullptr, nullptr);
}
