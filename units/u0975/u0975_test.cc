// FILE: u0975_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0975, TC1_CallsTarget) {
  int size{};
  ceres::DynamicCostFunction object{};
  object.AddParameterBlock(size);
}
