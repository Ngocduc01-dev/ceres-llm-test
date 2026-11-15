// FILE: u1525_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1525, TC1_CallsTarget) {
  int size{};
  ceres::Problem object{};
  object.AddParameterBlock(nullptr, size);
}
