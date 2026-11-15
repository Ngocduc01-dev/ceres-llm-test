// FILE: u1348_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END
TEST(u1348_Test, TC1_CallsTarget) {
  ceres::internal::BlockRandomAccessDiagonalMatrix target{};
}

// P2: START -> 1 -> END
TEST(u1348_Test, TC2_CallsTarget) {
  ceres::internal::BlockRandomAccessDiagonalMatrix target{};
}
