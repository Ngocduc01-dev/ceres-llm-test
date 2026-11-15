// FILE: u0742_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_cost_function.h"
#include "ceres/sized_cost_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0742, CallsTarget) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double residuals_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobians_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, residuals_data, jacobians_data);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0742, CallsTargetAlternate) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double residuals_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobians_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, residuals_data, jacobians_data);
}
