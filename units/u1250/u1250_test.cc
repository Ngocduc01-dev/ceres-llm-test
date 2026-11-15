// FILE: u1250_test.cc
#include "gtest/gtest.h"
#include "ceres/program_evaluator.h"

// P1: START -> 1 -> END
TEST(PlusTest, TC1_CallsTarget) {
  ProgramEvaluator object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Plus(a0, a1, a2);
}

