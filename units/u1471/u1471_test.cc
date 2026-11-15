// FILE: u1471_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/loss_function.h"
#include "ceres/corrector.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/small_blas.h"

// P1: START -> 1 -> END
TEST(u1471_Test, TC1_CallsTarget) {
  ceres::internal::ResidualBlock target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1471_Test, TC2_CallsTarget) {
  ceres::internal::ResidualBlock target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1471_Test, TC3_CallsTarget) {
  ceres::internal::ResidualBlock target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1471_Test, TC4_CallsTarget) {
  ceres::internal::ResidualBlock target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr);
}
