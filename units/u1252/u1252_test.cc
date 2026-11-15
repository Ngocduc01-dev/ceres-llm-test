// FILE: u1252_test.cc
#include "gtest/gtest.h"
#include "ceres/program_evaluator.h"

// P1: START -> 1 -> END
TEST(u1252_Test, TC1_CallsTarget) {
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> target{};
  target.NumEffectiveParameters();
}
