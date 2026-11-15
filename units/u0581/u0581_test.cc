// FILE: u0581_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.cc"

namespace ceres {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0581, CallsTarget) {
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobian_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  QuaternionPlusJacobianImpl(x_data, jacobian_ptr_data);
}
}  // namespace ceres
