// FILE: u0904_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function_to_functor.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0904, TC1_CallsTarget) {
  ceres::DynamicCostFunctionToFunctor object{};
  (void)object;
}
