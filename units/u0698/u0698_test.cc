// FILE: u0698_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0698, CallsTarget) {
  double angle_axis_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  AngleAxisToRotationMatrix(angle_axis_data, {});
}
}  // namespace ceres
