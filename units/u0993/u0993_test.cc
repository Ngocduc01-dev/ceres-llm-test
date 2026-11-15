// FILE: u0993_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0993, TC1_CallsTarget) {
  double a{};
  ceres_create_huber_loss_function_data(a);
}
