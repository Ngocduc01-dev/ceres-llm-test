// FILE: u1484_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1484_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.EvaluateResidualBlockAssumingParametersUnchanged(nullptr, nullptr, nullptr, nullptr, nullptr);
}
