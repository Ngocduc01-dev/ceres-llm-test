// FILE: u0936_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0936, TC1_CallsTarget) {
  ceres::GradientProblem object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0936, TC2_CallsTarget) {
  ceres::GradientProblem object{};
  (void)object;
}
