// FILE: u1490_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver.h"
#include "ceres/minimizer.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_step_evaluator.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END
TEST(u1490_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1490_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1490_Test, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1490_Test, TC4_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.Minimize(nullptr, nullptr, nullptr);
}
