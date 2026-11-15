// FILE: u0743_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/internal/variadic_evaluate.h"
#include "ceres/numeric_diff_first_order_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0743, CallsTarget) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cost_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double gradient_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, cost_data, gradient_data);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0743, CallsTargetAlternate) {
  double parameters_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cost_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double gradient_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Evaluate(parameters_data, cost_data, gradient_data);
}
