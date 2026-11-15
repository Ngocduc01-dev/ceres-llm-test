// FILE: u0847_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"

// P1: START -> 1 -> END
TEST(covariance_matrixTest, TC1_CallsTarget) {
  CovarianceImpl object{};
  object.covariance_matrix();
}

