// FILE: u1049_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1049, TC1_CallsTarget) {
  ceres::GradientProblem object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1049, TC2_CallsTarget) {
  ceres::GradientProblem object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}
