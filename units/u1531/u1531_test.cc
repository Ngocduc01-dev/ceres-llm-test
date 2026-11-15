// FILE: u1531_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1531, TC1_CallsTarget) {
  CovarianceBlocks covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.Compute(covariance_blocks, nullptr);
}
