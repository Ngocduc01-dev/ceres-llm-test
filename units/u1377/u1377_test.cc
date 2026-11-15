// FILE: u1377_test.cc
#include "gtest/gtest.h"
#include "ceres/eigen_vector_ops.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END
TEST(u1377_Test, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.ComputeTrustRegionStep();
}

// P2: START -> 1 -> END
TEST(u1377_Test, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.ComputeTrustRegionStep();
}

// P3: START -> 1 -> END
TEST(u1377_Test, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.ComputeTrustRegionStep();
}

// P4: START -> 1 -> END
TEST(u1377_Test, TC4_CallsTarget) {
  ceres::internal::TrustRegionMinimizer target{};
  target.ComputeTrustRegionStep();
}
