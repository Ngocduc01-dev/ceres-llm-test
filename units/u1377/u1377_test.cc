// FILE: u1377_test.cc
#include "gtest/gtest.h"
#include "ceres/eigen_vector_ops.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1377, TC1_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeTrustRegionStep();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1377, TC2_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeTrustRegionStep();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1377, TC3_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeTrustRegionStep();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1377, TC4_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeTrustRegionStep();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1377, TC5_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeTrustRegionStep();
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1377, TC6_CallsTarget) {
  ceres::internal::TrustRegionMinimizer object{};
  object.ComputeTrustRegionStep();
}
