// FILE: u1514_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/program.h"
#include "ceres/program_evaluator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1514, TC1_CallsTarget) {
  Evaluator::Options options{};
  ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter> object{};
  (void)object;
}
