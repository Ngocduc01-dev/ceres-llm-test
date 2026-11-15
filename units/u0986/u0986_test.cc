// FILE: u0986_test.cc
#include "gtest/gtest.h"
#include "ceres/block_evaluate_preparer.h"

// P1: START -> 1 -> END
TEST(InitTest, TC1_CallsTarget) {
  BlockEvaluatePreparer object{};
  int a0[5] = {};
  int a1 = 0;
  object.Init(a0, a1);
}

