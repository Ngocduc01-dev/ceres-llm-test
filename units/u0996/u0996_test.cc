// FILE: u0996_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END
TEST(ceres_create_arctan_loss_function_dataTest, TC1_CallsTarget) {
  double a0 = 0.0;
  ceres_create_arctan_loss_function_data(a0);
}

