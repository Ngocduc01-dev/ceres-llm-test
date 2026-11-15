// FILE: u0744_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0744, CallsTarget) {
  double quaternion_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  RotationMatrixToQuaternion({}, quaternion_data);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0744, CallsTargetAlternate) {
  double quaternion_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  RotationMatrixToQuaternion({}, quaternion_data);
}
}  // namespace ceres
