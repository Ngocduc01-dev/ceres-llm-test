// FILE: u0871_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0871, TC1_CallsTarget) {
  ceres::LossFunction object{};
  object.~LossFunction();
}
