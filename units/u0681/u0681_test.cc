// FILE: u0681_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"
#include "ceres/line_search_minimizer.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0681, PathP1) {
  ceres::internal::SteepestDescent target;
  ceres::internal::LineSearchMinimizer::State previous{};
  ceres::internal::LineSearchMinimizer::State current{};
  current.gradient = ceres::internal::Vector::Zero(1);
  ceres::internal::Vector search_direction(1);
  target.NextDirection(previous, current, &search_direction);
}
