// FILE: u1531_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(u1531_Test, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.Compute(nullptr, nullptr);
}
