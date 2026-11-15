// FILE: u1383_test.cc
#include "gtest/gtest.h"
#include "ceres/block_evaluate_preparer.h"
#include "ceres/block_jacobian_writer.h"

// P1: START -> 1 -> END
TEST(u1383_Test, TC1_CallsTarget) {
  ceres::internal::BlockJacobianWriter target{};
  target.CreateEvaluatePreparers(nullptr);
}

// P2: START -> 1 -> END
TEST(u1383_Test, TC2_CallsTarget) {
  ceres::internal::BlockJacobianWriter target{};
  target.CreateEvaluatePreparers(nullptr);
}
