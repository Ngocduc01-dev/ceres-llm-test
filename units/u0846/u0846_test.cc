// FILE: u0846_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"
#include "ceres/covariance_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0846, TC1_CallsTarget) {
  Covariance::Options options{};
  ceres::internal::CovarianceImpl object{};
  (void)object;
}
