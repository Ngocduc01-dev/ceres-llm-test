// FILE: u0776_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0776, TC1_CallsTarget) {
  LinearSolverType type{};
  ceres::LinearSolverTypeToString(type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0776, TC2_CallsTarget) {
  LinearSolverType type{};
  ceres::LinearSolverTypeToString(type);
}
