// FILE: u1410_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1410_Test, TC1_CallsTarget) {
  LexicographicallyOrderResidualBlocks(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1410_Test, TC2_CallsTarget) {
  LexicographicallyOrderResidualBlocks(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1410_Test, TC3_CallsTarget) {
  LexicographicallyOrderResidualBlocks(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1410_Test, TC4_CallsTarget) {
  LexicographicallyOrderResidualBlocks(nullptr, nullptr, nullptr);
}
