// FILE: u0764_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0764, TC1_CallsTarget) {
  std::ostream s{};
  LinearSolverTerminationType type{};
  ceres::internal::operator<<(s, type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0764, TC2_CallsTarget) {
  std::ostream s{};
  LinearSolverTerminationType type{};
  ceres::internal::operator<<(s, type);
}
