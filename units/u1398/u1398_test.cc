// FILE: u1398_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"
#include "ceres/scratch_evaluate_preparer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1398, TC1_CallsTarget) {
  Program program{};
  unsigned int num_threads{};
  ceres::internal::ScratchEvaluatePreparer object{};
  object.Create(program, num_threads);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1398, TC2_CallsTarget) {
  Program program{};
  unsigned int num_threads{};
  ceres::internal::ScratchEvaluatePreparer object{};
  object.Create(program, num_threads);
}
