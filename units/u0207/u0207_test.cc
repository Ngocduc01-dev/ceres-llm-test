// FILE: u0207_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AngleAxisToRotationMatrixTest, TC1_P1_ColumnMajorPointer) {
  const double angle_axis[3] = {0.3, -0.7, 0.5};
  double R[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  ceres::AngleAxisToRotationMatrix<double>(angle_axis, R);
}
