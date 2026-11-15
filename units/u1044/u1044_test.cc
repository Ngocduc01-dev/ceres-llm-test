// FILE: u1044_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1044, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.CopyParameterBlockStateToUserState();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1044, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.CopyParameterBlockStateToUserState();
}
