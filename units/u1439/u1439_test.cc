// FILE: u1439_test.cc
#include "gtest/gtest.h"
#include "ceres/block_evaluate_preparer.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/casts.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1439_Test, TC1_CallsTarget) {
  ceres::internal::BlockEvaluatePreparer target{};
  target.Prepare(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1439_Test, TC2_CallsTarget) {
  ceres::internal::BlockEvaluatePreparer target{};
  target.Prepare(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1439_Test, TC3_CallsTarget) {
  ceres::internal::BlockEvaluatePreparer target{};
  target.Prepare(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1439_Test, TC4_CallsTarget) {
  ceres::internal::BlockEvaluatePreparer target{};
  target.Prepare(nullptr, nullptr, nullptr, nullptr);
}
