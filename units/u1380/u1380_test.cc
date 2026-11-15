// FILE: u1380_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1380, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValuesUsingSuiteSparseQR();
}
