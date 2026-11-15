// FILE: u0501_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1 calls AngleAxisRotatePoint(const T angle_axis[3], const T pt[3], T result[3]).
TEST(Unitu0501, CallsTarget) {
  double angle_axis_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double pt_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double result_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  AngleAxisRotatePoint(angle_axis_data, pt_data, result_data);
}
}  // namespace ceres
