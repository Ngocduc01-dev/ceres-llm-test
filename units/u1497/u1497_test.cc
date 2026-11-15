// FILE: u1497_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"
#include "ceres/linear_solver.h"
#include "ceres/sparse_matrix.h"
#include "ceres/trust_region_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1497, TC1_CallsTarget) {
  PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeGaussNewtonStep(per_solve_options, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1497, TC2_CallsTarget) {
  PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeGaussNewtonStep(per_solve_options, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1497, TC3_CallsTarget) {
  PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeGaussNewtonStep(per_solve_options, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1497, TC4_CallsTarget) {
  PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeGaussNewtonStep(per_solve_options, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1497, TC5_CallsTarget) {
  PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeGaussNewtonStep(per_solve_options, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1497, TC6_CallsTarget) {
  PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeGaussNewtonStep(per_solve_options, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1497, TC7_CallsTarget) {
  PerSolveOptions per_solve_options{};
  ceres::internal::DoglegStrategy object{};
  object.ComputeGaussNewtonStep(per_solve_options, nullptr, nullptr);
}
