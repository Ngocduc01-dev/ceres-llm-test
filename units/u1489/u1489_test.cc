// FILE: u1489_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"
#include "ceres/linear_solver.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/sparse_matrix.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END
TEST(u1489_Test, TC1_CallsTarget) {
  ceres::internal::LevenbergMarquardtStrategy target{};
  target.ComputeStep(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1489_Test, TC2_CallsTarget) {
  ceres::internal::LevenbergMarquardtStrategy target{};
  target.ComputeStep(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1489_Test, TC3_CallsTarget) {
  ceres::internal::LevenbergMarquardtStrategy target{};
  target.ComputeStep(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1489_Test, TC4_CallsTarget) {
  ceres::internal::LevenbergMarquardtStrategy target{};
  target.ComputeStep(nullptr, nullptr, nullptr, nullptr);
}
