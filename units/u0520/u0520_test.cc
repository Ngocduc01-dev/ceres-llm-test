// FILE: u0520_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// Path P1 calls Plus(const double * x_ptr, const double * delta_ptr, double * x_plus_delta_ptr) const.
TEST(Unitu0520, CallsTarget) {
  double x_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_plus_delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Plus(x_ptr_data, delta_ptr_data, x_plus_delta_ptr_data);
}

// Path P2 calls Plus(const double * x_ptr, const double * delta_ptr, double * x_plus_delta_ptr) const on the alternate CFG path.
TEST(Unitu0520, CallsTargetAlternate) {
  double x_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_plus_delta_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Plus(x_ptr_data, delta_ptr_data, x_plus_delta_ptr_data);
}
