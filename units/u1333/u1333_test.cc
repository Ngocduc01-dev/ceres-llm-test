// FILE: u1333_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1333, TC1_CallsTarget) {
  int index{};
  double upper_bound{};
  ceres::Problem object{};
  object.SetParameterUpperBound(nullptr, index, upper_bound);
}
