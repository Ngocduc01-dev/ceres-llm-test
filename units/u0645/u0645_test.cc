// FILE: u0645_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1 calls EulerAnglesToRotationMatrix(const T* euler, const MatrixAdapter<T, row_stride, col_stride>& R).
TEST(Unitu0645, CallsTarget) {
  double euler_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  EulerAnglesToRotationMatrix(euler_data, {});
}
}  // namespace ceres
