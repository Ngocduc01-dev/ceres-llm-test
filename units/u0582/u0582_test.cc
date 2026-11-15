// FILE: u0582_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.cc"

namespace ceres {
// Path P1 calls QuaternionMinusJacobianImpl(const double* x, double* jacobian_ptr).
TEST(Unitu0582, CallsTarget) {
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobian_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  QuaternionMinusJacobianImpl(x_data, jacobian_ptr_data);
}
}  // namespace ceres
