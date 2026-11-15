// FILE: u0905_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0905, TC1_CallsTarget) {
  Ownership ownership{};
  ceres::LossFunctionWrapper object{};
  object.Reset(nullptr, ownership);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0905, TC2_CallsTarget) {
  Ownership ownership{};
  ceres::LossFunctionWrapper object{};
  object.Reset(nullptr, ownership);
}
