// FILE: u0800_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"
#include "ceres/polynomial.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0800, TC1_CallsTarget) {
  Vector polynomial{};
  ceres::internal::(anonymous)::BuildCompanionMatrix(polynomial, nullptr);
}
