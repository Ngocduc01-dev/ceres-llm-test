// FILE: u0889_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0889, TC1_CallsTarget) {
  ceres::internal::ResidualBlock object{};
  object.loss_function();
}
