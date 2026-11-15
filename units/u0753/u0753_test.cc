// FILE: u0753_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// P1: START -> 1 -> END
TEST(PreconditionerForZeroEBlocksTest, TC1_CallsTarget) {
  Preconditioner object{};
  PreconditionerType a0{};
  object.PreconditionerForZeroEBlocks(a0);
}

// P2: START -> 1 -> END
TEST(PreconditionerForZeroEBlocksTest, TC2_CallsTarget) {
  Preconditioner object{};
  PreconditionerType a0{};
  object.PreconditionerForZeroEBlocks(a0);
}

