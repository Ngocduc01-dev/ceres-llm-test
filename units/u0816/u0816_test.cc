// FILE: u0816_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(ComputeBlockPairsInPreconditionerTest, TC1_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  CompressedRowBlockStructure & bs a0{};
  object.ComputeBlockPairsInPreconditioner(a0);
}

// P2: START -> 1 -> END
TEST(ComputeBlockPairsInPreconditionerTest, TC2_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  CompressedRowBlockStructure & bs a0{};
  object.ComputeBlockPairsInPreconditioner(a0);
}

// P3: START -> 1 -> END
TEST(ComputeBlockPairsInPreconditionerTest, TC3_CallsTarget) {
  VisibilityBasedPreconditioner object{};
  CompressedRowBlockStructure & bs a0{};
  object.ComputeBlockPairsInPreconditioner(a0);
}

