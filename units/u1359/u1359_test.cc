// FILE: u1359_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/scratch_evaluate_preparer.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1359_Test, TC1_CallsTarget) {
  ceres::internal::ScratchEvaluatePreparer target{};
  target.Prepare(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1359_Test, TC2_CallsTarget) {
  ceres::internal::ScratchEvaluatePreparer target{};
  target.Prepare(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1359_Test, TC3_CallsTarget) {
  ceres::internal::ScratchEvaluatePreparer target{};
  target.Prepare(nullptr, nullptr, nullptr, nullptr);
}
