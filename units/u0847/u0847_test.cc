// FILE: u0847_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0847, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.covariance_matrix();
}
