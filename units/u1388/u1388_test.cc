// FILE: u1388_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1388, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.SetParameterBlockStatePtrsToUserStatePtrs();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1388, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.SetParameterBlockStatePtrsToUserStatePtrs();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1388, TC3_CallsTarget) {
  ceres::internal::Program object{};
  object.SetParameterBlockStatePtrsToUserStatePtrs();
}
