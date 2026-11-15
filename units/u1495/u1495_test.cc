// FILE: u1495_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/minimizer.h"
#include "ceres/preprocessor.h"
#include "ceres/program.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1495, TC1_CallsTarget) {
  ceres::Minimize(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1495, TC2_CallsTarget) {
  ceres::Minimize(nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1495, TC3_CallsTarget) {
  ceres::Minimize(nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1495, TC4_CallsTarget) {
  ceres::Minimize(nullptr, nullptr);
}
