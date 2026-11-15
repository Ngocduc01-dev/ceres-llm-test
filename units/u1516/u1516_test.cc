// FILE: u1516_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"
#include "ceres/linear_solver.h"
#include "ceres/sparse_matrix.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END
TEST(u1516_Test, TC1_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.ComputeStep(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1516_Test, TC2_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.ComputeStep(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1516_Test, TC3_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.ComputeStep(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1516_Test, TC4_CallsTarget) {
  ceres::internal::DoglegStrategy target{};
  target.ComputeStep(nullptr, nullptr, nullptr, nullptr);
}
