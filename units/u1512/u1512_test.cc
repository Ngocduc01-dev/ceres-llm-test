// FILE: u1512_test.cc
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1512, TC1_CallsTarget) {
  EvaluateOptions evaluate_options{};
  ceres::Problem object{};
  object.Evaluate(evaluate_options, nullptr, nullptr, nullptr, nullptr);
}
