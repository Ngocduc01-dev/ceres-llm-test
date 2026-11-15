// FILE: u0975_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function.h"

// P1: START -> 1 -> END
TEST(AddParameterBlockTest, TC1_CallsTarget) {
  DynamicCostFunction object{};
  int a0 = 0;
  object.AddParameterBlock(a0);
}

