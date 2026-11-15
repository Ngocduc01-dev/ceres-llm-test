// FILE: u0172_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(HuberLossConstructor, TC1_SinglePath) {
  ceres::HuberLoss loss(2.5);
  (void)loss;
}
