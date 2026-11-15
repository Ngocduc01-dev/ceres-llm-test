// FILE: u1466_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/evaluator.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(u1466_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.DoInnerIterationsIfNeeded();
}

// P2: START -> 1 -> END
TEST(u1466_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.DoInnerIterationsIfNeeded();
}

// P3: START -> 1 -> END
TEST(u1466_Test, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.DoInnerIterationsIfNeeded();
}

// P4: START -> 1 -> END
TEST(u1466_Test, TC4_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.DoInnerIterationsIfNeeded();
}
