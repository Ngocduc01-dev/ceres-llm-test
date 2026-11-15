// FILE: u1529_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/manifold.h"
#include "ceres/numeric_diff_options.h"
#include "ceres/problem.h"
#include "ceres/gradient_checking_cost_function.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1529_Test, TC1_CallsTarget) {
  CreateGradientCheckingProblemImpl(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1529_Test, TC2_CallsTarget) {
  CreateGradientCheckingProblemImpl(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1529_Test, TC3_CallsTarget) {
  CreateGradientCheckingProblemImpl(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1529_Test, TC4_CallsTarget) {
  CreateGradientCheckingProblemImpl(nullptr, nullptr, nullptr, nullptr);
}
