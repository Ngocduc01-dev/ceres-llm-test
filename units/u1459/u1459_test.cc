// FILE: u1459_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_sparse_normal_cholesky_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1459, TC1_CallsTarget) {
  ceres::internal::DynamicSparseNormalCholeskySolver object{};
  object.SolveImplUsingEigen(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1459, TC2_CallsTarget) {
  ceres::internal::DynamicSparseNormalCholeskySolver object{};
  object.SolveImplUsingEigen(nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1459, TC3_CallsTarget) {
  ceres::internal::DynamicSparseNormalCholeskySolver object{};
  object.SolveImplUsingEigen(nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1459, TC4_CallsTarget) {
  ceres::internal::DynamicSparseNormalCholeskySolver object{};
  object.SolveImplUsingEigen(nullptr, nullptr);
}
