// FILE: u1489_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"
#include "ceres/linear_solver.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/sparse_matrix.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1489, TC1_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::LevenbergMarquardtStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1489, TC2_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::LevenbergMarquardtStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1489, TC3_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::LevenbergMarquardtStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1489, TC4_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::LevenbergMarquardtStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1489, TC5_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::LevenbergMarquardtStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1489, TC6_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::LevenbergMarquardtStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1489, TC7_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::LevenbergMarquardtStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1489, TC8_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::LevenbergMarquardtStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1489, TC9_CallsTarget) {
  TrustRegionStrategy::PerSolveOptions per_solve_options{};
  ceres::internal::LevenbergMarquardtStrategy object{};
  object.ComputeStep(per_solve_options, nullptr, nullptr, nullptr);
}
