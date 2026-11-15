// FILE: u0905_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END
TEST(ResetTest, TC1_CallsTarget) {
  LossFunctionWrapper object{};
  Ownership a1{};
  object.Reset(nullptr, a1);
}

// P2: START -> 1 -> END
TEST(ResetTest, TC2_CallsTarget) {
  LossFunctionWrapper object{};
  Ownership a1{};
  object.Reset(nullptr, a1);
}

