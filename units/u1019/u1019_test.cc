// FILE: u1019_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"
#include "ceres/program_evaluator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1019, TC1_CallsTarget) {
  ceres::internal::ProgramEvaluator object{};
  object.Statistics();
}
