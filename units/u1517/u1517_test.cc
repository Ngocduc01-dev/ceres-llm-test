// FILE: u1517_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1517_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.AddResidualBlock(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1517_Test, TC2_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.AddResidualBlock(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1517_Test, TC3_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.AddResidualBlock(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1517_Test, TC4_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.AddResidualBlock(nullptr, nullptr, nullptr, nullptr);
}
