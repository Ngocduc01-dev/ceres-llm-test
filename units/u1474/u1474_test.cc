// FILE: u1474_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"
#include "ceres/program_evaluator.h"

// P1: START -> 1 -> END
TEST(u1474_Test, TC1_CallsTarget) {
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> target{};
  target.CreateEvaluatorScratch(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1474_Test, TC2_CallsTarget) {
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> target{};
  target.CreateEvaluatorScratch(nullptr, nullptr);
}
