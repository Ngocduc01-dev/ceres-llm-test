// FILE: u0800_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"
#include "ceres/polynomial.cc"

// P1: START -> 1 -> END
TEST(BuildCompanionMatrixTest, TC1_CallsTarget) {
  Vector & polynomial a0{};
  BuildCompanionMatrix(a0, nullptr);
}

