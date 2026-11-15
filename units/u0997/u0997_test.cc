// FILE: u0997_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0997, TC1_CallsTarget) {
  double a{};
  double b{};
  ceres_create_tolerant_loss_function_data(a, b);
}
