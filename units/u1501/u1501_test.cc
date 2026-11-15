// FILE: u1501_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1501, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.CreateReducedProgram(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1501, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.CreateReducedProgram(nullptr, nullptr, nullptr);
}
