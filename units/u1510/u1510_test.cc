// FILE: u1510_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"

// P1: START -> 1 -> END
TEST(u1510_Test, TC1_CallsTarget) {
  ceres::Covariance target{};
  target.GetCovarianceMatrixInTangentSpace(nullptr, nullptr);
}
