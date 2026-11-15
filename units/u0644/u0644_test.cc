// FILE: u0644_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1 calls RotationMatrixToAngleAxis(const MatrixAdapter<const T, row_stride, col_stride>& R, T* angle_axis).
TEST(Unitu0644, CallsTarget) {
  double angle_axis_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  RotationMatrixToAngleAxis({}, angle_axis_data);
}
}  // namespace ceres
