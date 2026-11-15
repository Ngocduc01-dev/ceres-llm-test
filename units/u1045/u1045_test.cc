// FILE: u1045_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(NumParametersTest, TC1_CallsTarget) {
  Program object{};
  object.NumParameters();
}

// P2: START -> 1 -> END
TEST(NumParametersTest, TC2_CallsTarget) {
  Program object{};
  object.NumParameters();
}

