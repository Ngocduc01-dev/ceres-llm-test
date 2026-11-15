// FILE: u1503_test.cc
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1503_Test, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValuesUsingDenseSVD();
}

// P2: START -> 1 -> END
TEST(u1503_Test, TC2_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValuesUsingDenseSVD();
}

// P3: START -> 1 -> END
TEST(u1503_Test, TC3_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValuesUsingDenseSVD();
}

// P4: START -> 1 -> END
TEST(u1503_Test, TC4_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValuesUsingDenseSVD();
}
