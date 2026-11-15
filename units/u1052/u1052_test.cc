// FILE: u1052_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/normal_prior.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1052, TC1_CallsTarget) {
  ceres::NormalPrior object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1052, TC2_CallsTarget) {
  ceres::NormalPrior object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}
