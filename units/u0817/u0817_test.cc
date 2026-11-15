// FILE: u0817_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0817, TC1_CallsTarget) {
  ceres::GradientProblem object{};
  object.manifold();
}
