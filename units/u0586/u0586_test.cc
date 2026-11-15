// FILE: u0586_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

// Path P1 calls PlusImpl(const double* x, const double* delta, double* x_plus_delta, std::index_sequence<Index0, Indices>) const.
TEST(Unitu0586, CallsTarget) {
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double delta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_plus_delta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.PlusImpl(x_data, delta_data, x_plus_delta_data, {});
}
