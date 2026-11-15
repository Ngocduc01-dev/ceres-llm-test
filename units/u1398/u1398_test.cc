// FILE: u1398_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"
#include "ceres/scratch_evaluate_preparer.h"

// P1: START -> 1 -> END
TEST(u1398_Test, TC1_CallsTarget) {
  ceres::internal::ScratchEvaluatePreparer target{};
  target.Create(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1398_Test, TC2_CallsTarget) {
  ceres::internal::ScratchEvaluatePreparer target{};
  target.Create(nullptr, nullptr);
}
