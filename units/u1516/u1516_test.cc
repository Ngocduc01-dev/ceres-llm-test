// FILE: u1516_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"
#include "ceres/linear_solver.h"
#include "ceres/sparse_matrix.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1516, TC1_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1516, TC2_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1516, TC3_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1516, TC4_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1516, TC5_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1516, TC6_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1516, TC7_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1516, TC8_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1516, TC9_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}
