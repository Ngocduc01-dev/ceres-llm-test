// FILE: u1004_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1004, TC1_CallsTarget) {
  ceres::internal::LevenbergMarquardtStrategy object{};
  object.StepIsInvalid();
}
