// FILE: u1454_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/inner_product_computer.h"
#include "ceres/linear_solver.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/sparse_normal_cholesky_solver.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1454_Test, TC1_CallsTarget) {
  ceres::internal::SparseNormalCholeskySolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1454_Test, TC2_CallsTarget) {
  ceres::internal::SparseNormalCholeskySolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1454_Test, TC3_CallsTarget) {
  ceres::internal::SparseNormalCholeskySolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1454_Test, TC4_CallsTarget) {
  ceres::internal::SparseNormalCholeskySolver target{};
  target.SolveImpl(nullptr, nullptr, nullptr, nullptr);
}
