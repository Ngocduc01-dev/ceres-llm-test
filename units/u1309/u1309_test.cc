// FILE: u1309_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"
#include "ceres/program_evaluator.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1309_Test, TC1_CallsTarget) {
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> target{};
  target.BuildResidualLayout(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1309_Test, TC2_CallsTarget) {
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> target{};
  target.BuildResidualLayout(nullptr, nullptr);
}
