// FILE: u0845_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0845, TC1_CallsTarget) {
  ceres::Covariance object{};
  object.~Covariance();
}
