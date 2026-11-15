// FILE: u1323_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"

// P1: START -> 1 -> END
TEST(u1323_Test, TC1_CallsTarget) {
  ceres::Covariance target{};
  target.GetCovarianceBlockInTangentSpace(nullptr, nullptr, nullptr);
}
