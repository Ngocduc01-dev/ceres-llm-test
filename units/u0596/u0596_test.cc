// FILE: u0596_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.cc"

namespace ceres {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0596, CallsTarget) {
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double delta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_plus_delta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  QuaternionPlusImpl(x_data, delta_data, x_plus_delta_data);
}
}  // namespace ceres
