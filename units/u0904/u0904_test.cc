// FILE: u0904_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function_to_functor.h"

// P1: START -> 1 -> END
TEST(Unit_u0904, TC1_CallsTarget) {
  DynamicCostFunctionToFunctor object{};
}

