// FILE: u1155_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1155, TC1_CallsTarget) {
  ceres::Problem object{};
  object.HasParameterBlock(nullptr);
}
