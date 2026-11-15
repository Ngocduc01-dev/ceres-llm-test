// FILE: u1366_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END
TEST(u1366_Test, TC1_CallsTarget) {
  ceres::internal::ParameterBlock target{};
  target.SetManifold(nullptr);
}

// P2: START -> 1 -> END
TEST(u1366_Test, TC2_CallsTarget) {
  ceres::internal::ParameterBlock target{};
  target.SetManifold(nullptr);
}

// P3: START -> 1 -> END
TEST(u1366_Test, TC3_CallsTarget) {
  ceres::internal::ParameterBlock target{};
  target.SetManifold(nullptr);
}
