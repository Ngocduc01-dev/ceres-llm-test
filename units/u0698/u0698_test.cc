// FILE: u0698_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1 calls AngleAxisToRotationMatrix(const T* angle_axis, const MatrixAdapter<T, row_stride, col_stride>& R).
TEST(Unitu0698, CallsTarget) {
  double angle_axis_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  AngleAxisToRotationMatrix(angle_axis_data, {});
}
}  // namespace ceres
