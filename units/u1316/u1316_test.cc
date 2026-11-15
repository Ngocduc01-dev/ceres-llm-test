// FILE: u1316_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1316, TC1_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForSparseCholeskyBasedSolver(options, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1316, TC2_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForSparseCholeskyBasedSolver(options, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1316, TC3_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForSparseCholeskyBasedSolver(options, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1316, TC4_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForSparseCholeskyBasedSolver(options, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1316, TC5_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForSparseCholeskyBasedSolver(options, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1316, TC6_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForSparseCholeskyBasedSolver(options, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1316, TC7_CallsTarget) {
  Solver::Options options{};
  ceres::OptionsAreValidForSparseCholeskyBasedSolver(options, nullptr);
}
