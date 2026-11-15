// FILE: u1195_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1195, TC1_CallsTarget) {
  LinearSolverType linear_solver_type{};
  ceres::internal::LinearSolver object{};
  object.LinearSolverForZeroEBlocks(linear_solver_type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1195, TC2_CallsTarget) {
  LinearSolverType linear_solver_type{};
  ceres::internal::LinearSolver object{};
  object.LinearSolverForZeroEBlocks(linear_solver_type);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1195, TC3_CallsTarget) {
  LinearSolverType linear_solver_type{};
  ceres::internal::LinearSolver object{};
  object.LinearSolverForZeroEBlocks(linear_solver_type);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1195, TC4_CallsTarget) {
  LinearSolverType linear_solver_type{};
  ceres::internal::LinearSolver object{};
  object.LinearSolverForZeroEBlocks(linear_solver_type);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1195, TC5_CallsTarget) {
  LinearSolverType linear_solver_type{};
  ceres::internal::LinearSolver object{};
  object.LinearSolverForZeroEBlocks(linear_solver_type);
}
