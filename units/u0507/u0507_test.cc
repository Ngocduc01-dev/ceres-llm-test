// FILE: u0507_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> 2 (đúng) -> 3 (đúng) -> END
TEST(TolerantLossConstructor, ValidParameters) {
  ceres::TolerantLoss loss(2.5, 1.5);
}
