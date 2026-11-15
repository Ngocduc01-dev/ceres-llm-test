// FILE: u0782_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// P1: START -> 1 -> END
TEST(RotationMatrixToEulerAnglesTest, TC1_CallsTarget) {
  MatrixAdapter< T, row_stride, col_stride>& R a0{};
  RotationMatrixToEulerAngles(a0, nullptr);
}

