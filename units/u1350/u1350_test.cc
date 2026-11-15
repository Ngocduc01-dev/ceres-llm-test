// FILE: u1350_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1350, TC1_CallsTarget) {
  double step_size_estimate{};
  double initial_cost{};
  double initial_gradient{};
  ceres::internal::LineSearch object{};
  object.Search(step_size_estimate, initial_cost, initial_gradient, nullptr);
}
