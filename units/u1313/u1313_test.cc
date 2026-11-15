// FILE: u1313_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"

// P1: START -> 1 -> END
TEST(u1313_Test, TC1_CallsTarget) {
  SchurEliminator<> target{};
  target.ChunkDiagonalBlockAndGradient(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1313_Test, TC2_CallsTarget) {
  SchurEliminator<> target{};
  target.ChunkDiagonalBlockAndGradient(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1313_Test, TC3_CallsTarget) {
  SchurEliminator<> target{};
  target.ChunkDiagonalBlockAndGradient(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1313_Test, TC4_CallsTarget) {
  SchurEliminator<> target{};
  target.ChunkDiagonalBlockAndGradient(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
