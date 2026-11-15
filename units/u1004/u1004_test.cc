// FILE: u1004_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

// P1: START -> 1 -> END
TEST(StepIsInvalidTest, TC1_CallsTarget) {
  LevenbergMarquardtStrategy object{};
  object.StepIsInvalid();
}

