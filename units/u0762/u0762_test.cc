// FILE: u0762_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"
#include "ceres/line_search_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0762, TC1_CallsTarget) {
  LineSearchMinimizer::State previous{};
  LineSearchMinimizer::State current{};
  ceres::internal::NonlinearConjugateGradient object{};
  object.NextDirection(previous, current, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0762, TC2_CallsTarget) {
  LineSearchMinimizer::State previous{};
  LineSearchMinimizer::State current{};
  ceres::internal::NonlinearConjugateGradient object{};
  object.NextDirection(previous, current, nullptr);
}
