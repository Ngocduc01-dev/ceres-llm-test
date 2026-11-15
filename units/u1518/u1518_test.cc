// FILE: u1518_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"

// P1: START -> 1 -> END
TEST(u1518_Test, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValues();
}

// P2: START -> 1 -> END
TEST(u1518_Test, TC2_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValues();
}

// P3: START -> 1 -> END
TEST(u1518_Test, TC3_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValues();
}

// P4: START -> 1 -> END
TEST(u1518_Test, TC4_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.ComputeCovarianceValues();
}
