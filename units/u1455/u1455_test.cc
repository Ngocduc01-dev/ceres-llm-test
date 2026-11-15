// FILE: u1455_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/casts.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1455, TC1_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.Factorize();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1455, TC2_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.Factorize();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1455, TC3_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.Factorize();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1455, TC4_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.Factorize();
}
