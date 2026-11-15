// FILE: u1322_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"

// P1: START -> 1 -> END
TEST(u1322_Test, TC1_CallsTarget) {
  ceres::Covariance target{};
  target.GetCovarianceBlock(nullptr, nullptr, nullptr);
}
