// FILE: u1339_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1339, TC1_CallsTarget) {
  ceres::Problem object{};
  object.ParameterBlockTangentSize(nullptr);
}
