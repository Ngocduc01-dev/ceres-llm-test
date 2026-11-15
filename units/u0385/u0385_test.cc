// FILE: u0385_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IdentityPreconditionerRightMultiplyAndAccumulate, TC1_P1) {
  const int num_rows = 3;
  ceres::internal::IdentityPreconditioner preconditioner(num_rows);
  const double x[3] = {1.0, -2.0, 3.0};
  double y[3] = {0.5, 4.0, -1.5};
  preconditioner.RightMultiplyAndAccumulate(x, y);
}
