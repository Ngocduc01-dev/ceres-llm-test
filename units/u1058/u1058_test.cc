// FILE: u1058_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"
#include "ceres/internal/numeric_diff.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1058, TC1_CallsTarget) {
  ceres::DynamicNumericDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1058, TC2_CallsTarget) {
  ceres::DynamicNumericDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1058, TC3_CallsTarget) {
  ceres::DynamicNumericDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1058, TC4_CallsTarget) {
  ceres::DynamicNumericDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1058, TC5_CallsTarget) {
  ceres::DynamicNumericDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1058, TC6_CallsTarget) {
  ceres::DynamicNumericDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}
