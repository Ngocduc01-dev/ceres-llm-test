// FILE: u1046_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(NumEffectiveParametersTest, TC1_CallsTarget) {
  Program object{};
  object.NumEffectiveParameters();
}

// P2: START -> 1 -> END
TEST(NumEffectiveParametersTest, TC2_CallsTarget) {
  Program object{};
  object.NumEffectiveParameters();
}

