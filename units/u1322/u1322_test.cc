// FILE: u1322_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1322, TC1_CallsTarget) {
  ceres::Covariance object{};
  object.GetCovarianceBlock(nullptr, nullptr, nullptr);
}
