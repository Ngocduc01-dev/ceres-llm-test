// FILE: u0745_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0745, CallsTarget) {
  double euler_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  EulerAnglesToRotation(euler_data, {});
}
}  // namespace ceres
