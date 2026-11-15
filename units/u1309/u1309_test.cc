// FILE: u1309_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"
#include "ceres/program_evaluator.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1309, TC1_CallsTarget) {
  Program program{};
  ceres::internal::ProgramEvaluator object{};
  object.BuildResidualLayout(program, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1309, TC2_CallsTarget) {
  Program program{};
  ceres::internal::ProgramEvaluator object{};
  object.BuildResidualLayout(program, nullptr);
}
