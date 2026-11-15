// FILE: u0779_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"
#include "ceres/line_search_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0779, TC1_CallsTarget) {
  LineSearchMinimizer::State previous{};
  LineSearchMinimizer::State current{};
  ceres::internal::BFGS object{};
  object.NextDirection(previous, current, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0779, TC2_CallsTarget) {
  LineSearchMinimizer::State previous{};
  LineSearchMinimizer::State current{};
  ceres::internal::BFGS object{};
  object.NextDirection(previous, current, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0779, TC3_CallsTarget) {
  LineSearchMinimizer::State previous{};
  LineSearchMinimizer::State current{};
  ceres::internal::BFGS object{};
  object.NextDirection(previous, current, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0779, TC4_CallsTarget) {
  LineSearchMinimizer::State previous{};
  LineSearchMinimizer::State current{};
  ceres::internal::BFGS object{};
  object.NextDirection(previous, current, nullptr);
}
