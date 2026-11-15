// FILE: u0275_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0275, PathP1) {
  // Scope exit invokes ~CovarianceImpl().
  ceres::Covariance::Options options;
  ceres::internal::CovarianceImpl object(options);
}
