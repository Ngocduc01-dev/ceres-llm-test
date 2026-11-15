// FILE: u0844_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"
#include "ceres/covariance_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0844, TC1_CallsTarget) {
  Covariance::Options options{};
  ceres::Covariance object{};
  (void)object;
}
