// FILE: u0969_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/line_search_minimizer.h"
#include "ceres/line_search_minimizer.cc"

// P1: START -> 1 -> END
TEST(EvaluateGradientNormsTest, TC1_CallsTarget) {
  Vector & x a1{};
  EvaluateGradientNorms(nullptr, a1, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(EvaluateGradientNormsTest, TC2_CallsTarget) {
  Vector & x a1{};
  EvaluateGradientNorms(nullptr, a1, nullptr, nullptr);
}

