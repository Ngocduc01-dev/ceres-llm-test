// FILE: u1044_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(CopyParameterBlockStateToUserStateTest, TC1_CallsTarget) {
  Program object{};
  object.CopyParameterBlockStateToUserState();
}

// P2: START -> 1 -> END
TEST(CopyParameterBlockStateToUserStateTest, TC2_CallsTarget) {
  Program object{};
  object.CopyParameterBlockStateToUserState();
}

