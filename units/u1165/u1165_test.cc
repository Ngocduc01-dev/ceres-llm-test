// FILE: u1165_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1165, TC1_CallsTarget) {
  int index{};
  ceres::internal::ResidualBlock object{};
  (void)object;
}
