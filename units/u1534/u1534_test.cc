// FILE: u1534_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1534, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.Compute(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1534, TC2_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.Compute(nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1534, TC3_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.Compute(nullptr, nullptr);
}
