// FILE: u1387_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1387, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.StateVectorToParameterBlocks(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1387, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.StateVectorToParameterBlocks(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1387, TC3_CallsTarget) {
  ceres::internal::Program object{};
  object.StateVectorToParameterBlocks(nullptr);
}
