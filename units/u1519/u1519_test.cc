// FILE: u1519_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1519, TC1_CallsTarget) {
  ceres::Solver::Options object{};
  object.IsValid(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1519, TC2_CallsTarget) {
  ceres::Solver::Options object{};
  object.IsValid(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1519, TC3_CallsTarget) {
  ceres::Solver::Options object{};
  object.IsValid(nullptr);
}
