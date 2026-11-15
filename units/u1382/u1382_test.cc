// FILE: u1382_test.cc
#include "gtest/gtest.h"
#include "ceres/program_evaluator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1382, TC1_CallsTarget) {
  ceres::internal::ProgramEvaluator object{};
  object.NumResiduals();
}
