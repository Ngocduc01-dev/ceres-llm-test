// FILE: u1395_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

// P1: START -> 1 -> END
TEST(u1395_Test, TC1_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.ComputeSubspaceDoglegStep(nullptr);
}

// P2: START -> 1 -> END
TEST(u1395_Test, TC2_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.ComputeSubspaceDoglegStep(nullptr);
}

// P3: START -> 1 -> END
TEST(u1395_Test, TC3_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.ComputeSubspaceDoglegStep(nullptr);
}

// P4: START -> 1 -> END
TEST(u1395_Test, TC4_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.ComputeSubspaceDoglegStep(nullptr);
}
