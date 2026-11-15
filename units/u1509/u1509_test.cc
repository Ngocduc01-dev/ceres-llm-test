// FILE: u1509_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1509, TC1_CallsTarget) {
  ceres::Covariance object{};
  object.GetCovarianceMatrix(nullptr, nullptr);
}
