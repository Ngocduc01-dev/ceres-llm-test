// FILE: u1277_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1277_Test, TC1_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.ScaleOffDiagonalCells();
}

// P2: START -> 1 -> END
TEST(u1277_Test, TC2_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.ScaleOffDiagonalCells();
}

// P3: START -> 1 -> END
TEST(u1277_Test, TC3_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
  target.ScaleOffDiagonalCells();
}
