// FILE: u0400_test.cc
#include "gtest/gtest.h"
#include "ceres/program_evaluator.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0400, PathP1) { ceres::internal::ProgramEvaluator::EvaluateScratch target; target.Init(1, 1, 1, 1); }
