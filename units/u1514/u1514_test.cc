// FILE: u1514_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/program.h"
#include "ceres/program_evaluator.h"

// P1: START -> 1 -> END
TEST(u1514_Test, TC1_CallsTarget) {
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> target{};
  target.ProgramEvaluator<EvaluatePreparer, JacobianWriter, JacobianFinalizer>(nullptr, nullptr);
}
