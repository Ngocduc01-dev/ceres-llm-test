// FILE: u0176_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(TukeyLossConstructorTest, TC1_P1_SinglePath) {
  ceres::TukeyLoss loss(2.7);
  (void)loss;
}
