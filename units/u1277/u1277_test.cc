// FILE: u1277_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1277, TC1_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ScaleOffDiagonalCells();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1277, TC2_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ScaleOffDiagonalCells();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1277, TC3_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ScaleOffDiagonalCells();
}
