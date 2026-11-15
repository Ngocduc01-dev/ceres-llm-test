// FILE: u0681_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"
#include "ceres/line_search_minimizer.h"

// Path P1 calls NextDirection(const LineSearchMinimizer::State &, const LineSearchMinimizer::State & current, Vector * search_direction).
TEST(Unitu0681, CallsTarget) {
  double search_direction_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.NextDirection({}, {}, search_direction_data);
}
