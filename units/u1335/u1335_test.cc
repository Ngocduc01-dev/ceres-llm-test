// FILE: u1335_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1335, TC1_CallsTarget) {
  int index{};
  ceres::Problem object{};
  object.GetParameterLowerBound(nullptr, index);
}
