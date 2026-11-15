// FILE: u0834_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0834, TC1_CallsTarget) {
  double squared_norm{};
  double[3] out{};
  ceres_stock_loss_function(nullptr, squared_norm, out);
}
