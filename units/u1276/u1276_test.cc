// FILE: u1276_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/evaluator.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(u1276_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.IterationZero();
}

// P2: START -> 1 -> END
TEST(u1276_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.IterationZero();
}

// P3: START -> 1 -> END
TEST(u1276_Test, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.IterationZero();
}

// P4: START -> 1 -> END
TEST(u1276_Test, TC4_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.IterationZero();
}
