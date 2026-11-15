// FILE: u0470_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> 2(sai) -> 6 -> 3(đúng) -> 4 -> END
// Phải là test đầu tiên gọi Evaluate để node 2 đi nhánh "sai" (khởi tạo lần đầu).
// Path P1: START -> CFG nodes -> END.
TEST(TolerantLossEvaluate, XGreaterThanThreshold) {
  ceres::TolerantLoss loss(1.5, 2.0);
  double rho[3];
  loss.Evaluate(100.0, rho);
}

// P2: START -> 1 -> 2(đúng) -> 3(sai) -> 5 -> END
// Path P1: START -> CFG nodes -> END.
TEST(TolerantLossEvaluate, XNotGreaterThanThreshold) {
  ceres::TolerantLoss loss(1.5, 2.0);
  double rho[3];
  loss.Evaluate(3.0, rho);
}
