// FILE: u1446_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1446_Test, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceSparsity(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1446_Test, TC2_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceSparsity(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1446_Test, TC3_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceSparsity(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1446_Test, TC4_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceSparsity(nullptr, nullptr);
}
