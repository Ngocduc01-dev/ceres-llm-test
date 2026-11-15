// FILE: u1045_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1045, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.NumParameters();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1045, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.NumParameters();
}
