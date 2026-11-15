// FILE: u1131_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(DeleteBlockTest, TC1_CallsTarget) {
  ProblemImpl object{};
  object.DeleteBlock(nullptr);
}

