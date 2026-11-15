// FILE: u0764_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(Unit_u0764, TC1_CallsTarget) {
  std::ostream & s a0{};
  LinearSolverTerminationType a1{};
  ceres::internal::operator<<(a0, a1);
}

// P2: START -> 1 -> END
TEST(Unit_u0764, TC2_CallsTarget) {
  std::ostream & s a0{};
  LinearSolverTerminationType a1{};
  ceres::internal::operator<<(a0, a1);
}

