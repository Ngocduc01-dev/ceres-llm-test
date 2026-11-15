// FILE: u1305_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_options.h"

// P1: START -> 1 -> END
TEST(u1305_Test, TC1_CallsTarget) {
  NumericDiff<PlusFunctor, RIDDERS, -1, ParameterDims<true>, -1, -1> target{};
  target.EvaluateJacobianForParameterBlock(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1305_Test, TC2_CallsTarget) {
  NumericDiff<PlusFunctor, RIDDERS, -1, ParameterDims<true>, -1, -1> target{};
  target.EvaluateJacobianForParameterBlock(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1305_Test, TC3_CallsTarget) {
  NumericDiff<PlusFunctor, RIDDERS, -1, ParameterDims<true>, -1, -1> target{};
  target.EvaluateJacobianForParameterBlock(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
