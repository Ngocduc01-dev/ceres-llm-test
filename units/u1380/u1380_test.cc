// FILE: u1380_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1380_Test, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValuesUsingSuiteSparseQR();
}
