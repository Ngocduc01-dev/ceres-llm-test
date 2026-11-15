// FILE: u1019_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"
#include "ceres/program_evaluator.h"

// P1: START -> 1 -> END
TEST(StatisticsTest, TC1_CallsTarget) {
  ProgramEvaluator object{};
  object.Statistics();
}

