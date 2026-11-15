// FILE: u1534_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(u1534_Test, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.Compute(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1534_Test, TC2_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.Compute(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1534_Test, TC3_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.Compute(nullptr, nullptr);
}
