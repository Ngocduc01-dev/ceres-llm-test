// FILE: u1257_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1257_Test, TC1_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.num_rows();
}
