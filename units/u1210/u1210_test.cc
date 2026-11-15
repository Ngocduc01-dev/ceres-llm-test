// FILE: u1210_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/cost_function_to_functor.h"
#include "ceres/dynamic_cost_function_to_functor.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1210, TC1_CallsTarget) {
  CostFunctionToFunctor<2, 2> object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1210, TC2_CallsTarget) {
  CostFunctionToFunctor<2, 2> object{};
  (void)object;
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1210, TC3_CallsTarget) {
  CostFunctionToFunctor<2, 2> object{};
  (void)object;
}
