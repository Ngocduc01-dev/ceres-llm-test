// FILE: u1496_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/schur_eliminator.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1496_Test, TC1_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.UpdateImpl(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1496_Test, TC2_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.UpdateImpl(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1496_Test, TC3_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.UpdateImpl(nullptr, nullptr);
}
