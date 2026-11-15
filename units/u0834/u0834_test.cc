// FILE: u0834_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END
TEST(ceres_stock_loss_functionTest, TC1_CallsTarget) {
  double a1 = 0.0;
  double a2 = 0.0;
  ceres_stock_loss_function(nullptr, a1, a2);
}

