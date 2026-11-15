// FILE: u1532_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1532_Test, TC1_CallsTarget) {
  ceres_problem_add_residual_block(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1532_Test, TC2_CallsTarget) {
  ceres_problem_add_residual_block(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
