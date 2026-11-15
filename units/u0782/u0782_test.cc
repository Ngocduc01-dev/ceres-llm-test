// FILE: u0782_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0782, TC1_CallsTarget) {
  MatrixAdapter<const T, row_stride, col_stride> R{};
  ceres::RotationMatrixToEulerAngles(R, nullptr);
}
