// FILE: u1407_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluation_callback.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1407_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.EvaluateResidualBlock(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1407_Test, TC2_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.EvaluateResidualBlock(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1407_Test, TC3_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.EvaluateResidualBlock(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1407_Test, TC4_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.EvaluateResidualBlock(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
