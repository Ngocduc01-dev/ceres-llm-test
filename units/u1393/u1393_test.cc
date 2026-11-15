// FILE: u1393_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_checking_cost_function.h"
#include "ceres/cost_function.h"
#include "ceres/gradient_checker.h"
#include "ceres/gradient_checking_cost_function.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1393, TC1_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1393, TC2_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1393, TC3_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1393, TC4_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1393, TC5_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1393, TC6_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}
