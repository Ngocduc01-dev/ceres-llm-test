// FILE: u1311_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END
TEST(u1311_Test, TC1_CallsTarget) {
  MinParameterBlock(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1311_Test, TC2_CallsTarget) {
  MinParameterBlock(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1311_Test, TC3_CallsTarget) {
  MinParameterBlock(nullptr, nullptr);
}
