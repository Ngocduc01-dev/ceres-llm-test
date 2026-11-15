// FILE: u0275_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"

TEST(Unit_u0275, PathP1) {
  // Path P1: START -> 1 -> END.
  // Scope exit invokes ~CovarianceImpl().
  ceres::Covariance::Options options;
  ceres::internal::CovarianceImpl object(options);
}
