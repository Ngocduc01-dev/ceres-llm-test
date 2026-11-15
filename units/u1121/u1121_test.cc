// FILE: u1121_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function_to_functor.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END
TEST(operator()Test, TC1_CallsTarget) {
  DynamicCostFunctionToFunctor object{};
  object.operator()(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(operator()Test, TC2_CallsTarget) {
  DynamicCostFunctionToFunctor object{};
  object.operator()(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(operator()Test, TC3_CallsTarget) {
  DynamicCostFunctionToFunctor object{};
  object.operator()(nullptr, nullptr);
}

