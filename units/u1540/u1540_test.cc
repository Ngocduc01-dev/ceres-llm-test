// FILE: u1540_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1540, TC1_CallsTarget) {
  ceres::Covariance object{};
  object.Compute(nullptr, nullptr);
}
