// FILE: u1459_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_sparse_normal_cholesky_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1459_Test, TC1_CallsTarget) {
  ceres::internal::DynamicSparseNormalCholeskySolver target{};
  target.SolveImplUsingEigen(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1459_Test, TC2_CallsTarget) {
  ceres::internal::DynamicSparseNormalCholeskySolver target{};
  target.SolveImplUsingEigen(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1459_Test, TC3_CallsTarget) {
  ceres::internal::DynamicSparseNormalCholeskySolver target{};
  target.SolveImplUsingEigen(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1459_Test, TC4_CallsTarget) {
  ceres::internal::DynamicSparseNormalCholeskySolver target{};
  target.SolveImplUsingEigen(nullptr, nullptr);
}
