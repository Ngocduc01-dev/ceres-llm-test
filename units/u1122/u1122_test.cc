// FILE: u1122_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1122, TC1_CallsTarget) {
  const double x{};
  const bool evaluate_gradient{};
  ceres::internal::LineSearchFunction object{};
  object.Evaluate(x, evaluate_gradient, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1122, TC2_CallsTarget) {
  const double x{};
  const bool evaluate_gradient{};
  ceres::internal::LineSearchFunction object{};
  object.Evaluate(x, evaluate_gradient, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1122, TC3_CallsTarget) {
  const double x{};
  const bool evaluate_gradient{};
  ceres::internal::LineSearchFunction object{};
  object.Evaluate(x, evaluate_gradient, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1122, TC4_CallsTarget) {
  const double x{};
  const bool evaluate_gradient{};
  ceres::internal::LineSearchFunction object{};
  object.Evaluate(x, evaluate_gradient, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1122, TC5_CallsTarget) {
  const double x{};
  const bool evaluate_gradient{};
  ceres::internal::LineSearchFunction object{};
  object.Evaluate(x, evaluate_gradient, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1122, TC6_CallsTarget) {
  const double x{};
  const bool evaluate_gradient{};
  ceres::internal::LineSearchFunction object{};
  object.Evaluate(x, evaluate_gradient, nullptr);
}
