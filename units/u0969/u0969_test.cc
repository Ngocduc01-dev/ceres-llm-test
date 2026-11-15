// FILE: u0969_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/line_search_minimizer.h"
#include "ceres/line_search_minimizer.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0969, TC1_CallsTarget) {
  Vector x{};
  ceres::internal::(anonymous)::EvaluateGradientNorms(nullptr, x, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0969, TC2_CallsTarget) {
  Vector x{};
  ceres::internal::(anonymous)::EvaluateGradientNorms(nullptr, x, nullptr, nullptr);
}
