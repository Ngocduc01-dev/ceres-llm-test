// FILE: u0833_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END
TEST(ceres_free_stock_loss_function_dataTest, TC1_CallsTarget) {
  ceres_free_stock_loss_function_data(nullptr);
}

