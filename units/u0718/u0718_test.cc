// FILE: u0718_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1 calls QuaternionToRotation(const T q[4], const MatrixAdapter<T, row_stride, col_stride>& R).
TEST(Unitu0718, CallsTarget) {
  double q_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  QuaternionToRotation(q_data, {});
}
}  // namespace ceres
