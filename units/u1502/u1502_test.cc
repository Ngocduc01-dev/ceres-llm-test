// FILE: u1502_test.cc
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"
#include "ceres/compressed_col_sparse_matrix_utils.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/parallel_for.h"
#include "ceres/problem_impl.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1502_Test, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValuesUsingEigenSparseQR();
}

// P2: START -> 1 -> END
TEST(u1502_Test, TC2_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValuesUsingEigenSparseQR();
}

// P3: START -> 1 -> END
TEST(u1502_Test, TC3_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValuesUsingEigenSparseQR();
}

// P4: START -> 1 -> END
TEST(u1502_Test, TC4_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValuesUsingEigenSparseQR();
}
