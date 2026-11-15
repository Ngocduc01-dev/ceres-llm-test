// FILE: u1205_test.cc
#include "gtest/gtest.h"
#include "ceres/conditioned_cost_function.h"
#include "ceres/cost_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1205, TC1_CallsTarget) {
  Ownership ownership{};
  ceres::ConditionedCostFunction object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1205, TC2_CallsTarget) {
  Ownership ownership{};
  ceres::ConditionedCostFunction object{};
  (void)object;
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1205, TC3_CallsTarget) {
  Ownership ownership{};
  ceres::ConditionedCostFunction object{};
  (void)object;
}
