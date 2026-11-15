// FILE: u0644_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0644, CallsTarget) {
  double angle_axis_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  RotationMatrixToAngleAxis({}, angle_axis_data);
}
}  // namespace ceres
