// FILE: u1522_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1522, TC1_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::WolfeLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1522, TC2_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::WolfeLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1522, TC3_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::WolfeLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1522, TC4_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::WolfeLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1522, TC5_CallsTarget) {
  const double step_size_estimate{};
  const double initial_cost{};
  const double initial_gradient{};
  ceres::internal::WolfeLineSearch object{};
  object.DoSearch(step_size_estimate, initial_cost, initial_gradient, nullptr);
}
