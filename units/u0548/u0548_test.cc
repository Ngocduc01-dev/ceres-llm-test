// FILE: u0548_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver_autodiff_function.h"

// Path P1 calls operator()(const T * parameters, T * residuals, T * jacobian) const.
TEST(Unitu0548, CallsTarget) {
  double jacobian_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.operator(jacobian_data);
}

// Path P2 calls operator()(const T * parameters, T * residuals, T * jacobian) const on the alternate CFG path.
TEST(Unitu0548, CallsTargetAlternate) {
  double jacobian_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.operator(jacobian_data);
}
