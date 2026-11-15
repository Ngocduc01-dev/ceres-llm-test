// FILE: u1332_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1332, TC1_CallsTarget) {
  int index{};
  double lower_bound{};
  ceres::Problem object{};
  object.SetParameterLowerBound(nullptr, index, lower_bound);
}
