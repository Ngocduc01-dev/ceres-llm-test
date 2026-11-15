// FILE: u1312_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(u1312_Test, TC1_CallsTarget) {
  SchurEliminator<> target{};
  target.NoEBlockRowsUpdate(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1312_Test, TC2_CallsTarget) {
  SchurEliminator<> target{};
  target.NoEBlockRowsUpdate(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1312_Test, TC3_CallsTarget) {
  SchurEliminator<> target{};
  target.NoEBlockRowsUpdate(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1312_Test, TC4_CallsTarget) {
  SchurEliminator<> target{};
  target.NoEBlockRowsUpdate(nullptr, nullptr, nullptr, nullptr, nullptr);
}
