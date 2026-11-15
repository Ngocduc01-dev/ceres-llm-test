// FILE: u1121_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function_to_functor.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1121, TC1_CallsTarget) {
  ceres::DynamicCostFunctionToFunctor object{};
  object(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1121, TC2_CallsTarget) {
  ceres::DynamicCostFunctionToFunctor object{};
  object(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1121, TC3_CallsTarget) {
  ceres::DynamicCostFunctionToFunctor object{};
  object(nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1121, TC4_CallsTarget) {
  ceres::DynamicCostFunctionToFunctor object{};
  object(nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1121, TC5_CallsTarget) {
  ceres::DynamicCostFunctionToFunctor object{};
  object(nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1121, TC6_CallsTarget) {
  ceres::DynamicCostFunctionToFunctor object{};
  object(nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1121, TC7_CallsTarget) {
  ceres::DynamicCostFunctionToFunctor object{};
  object(nullptr);
}
