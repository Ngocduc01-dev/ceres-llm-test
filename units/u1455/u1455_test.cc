// FILE: u1455_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/casts.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1455_Test, TC1_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.Factorize();
}

// P2: START -> 1 -> END
TEST(u1455_Test, TC2_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.Factorize();
}

// P3: START -> 1 -> END
TEST(u1455_Test, TC3_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.Factorize();
}

// P4: START -> 1 -> END
TEST(u1455_Test, TC4_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.Factorize();
}
