// FILE: u0740_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_first_order_function.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/jet.h"

// Path P1 calls Evaluate(const double *const parameters, double * cost, double * gradient) const.
TEST(Unitu0740, CallsTarget) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cost_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double gradient_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, cost_data, gradient_data);
}

// Path P2 calls Evaluate(const double *const parameters, double * cost, double * gradient) const on the alternate CFG path.
TEST(Unitu0740, CallsTargetAlternate) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cost_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double gradient_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, cost_data, gradient_data);
}
