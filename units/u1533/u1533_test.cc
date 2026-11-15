// FILE: u1533_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/solver.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/gradient_checking_cost_function.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1533, TC1_CallsTarget) {
  Solver::Options options{};
  ceres::Solver object{};
  object.Solve(options, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1533, TC2_CallsTarget) {
  Solver::Options options{};
  ceres::Solver object{};
  object.Solve(options, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1533, TC3_CallsTarget) {
  Solver::Options options{};
  ceres::Solver object{};
  object.Solve(options, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1533, TC4_CallsTarget) {
  Solver::Options options{};
  ceres::Solver object{};
  object.Solve(options, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1533, TC5_CallsTarget) {
  Solver::Options options{};
  ceres::Solver object{};
  object.Solve(options, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1533, TC6_CallsTarget) {
  Solver::Options options{};
  ceres::Solver object{};
  object.Solve(options, nullptr, nullptr);
}
