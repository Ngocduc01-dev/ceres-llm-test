// FILE: u1509_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"

// P1: START -> 1 -> END
TEST(u1509_Test, TC1_CallsTarget) {
  ceres::Covariance target{};
  target.GetCovarianceMatrix(nullptr, nullptr);
}
