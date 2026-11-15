// FILE: u1232_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(DeleteBlockTest, TC1_CallsTarget) {
  ProblemImpl object{};
  object.DeleteBlock(nullptr);
}

// P2: START -> 1 -> END
TEST(DeleteBlockTest, TC2_CallsTarget) {
  ProblemImpl object{};
  object.DeleteBlock(nullptr);
}

// P3: START -> 1 -> END
TEST(DeleteBlockTest, TC3_CallsTarget) {
  ProblemImpl object{};
  object.DeleteBlock(nullptr);
}

