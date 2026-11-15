// FILE: u1393_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_checking_cost_function.h"
#include "ceres/cost_function.h"
#include "ceres/gradient_checker.h"
#include "ceres/gradient_checking_cost_function.cc"

// P1: START -> 1 -> END
TEST(u1393_Test, TC1_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction target{};
  target.Evaluate(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1393_Test, TC2_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction target{};
  target.Evaluate(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1393_Test, TC3_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction target{};
  target.Evaluate(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1393_Test, TC4_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction target{};
  target.Evaluate(nullptr, nullptr, nullptr);
}
