// FILE: u1462_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_jacobian_writer.h"
#include "ceres/scratch_evaluate_preparer.h"

// P1: START -> 1 -> END
TEST(u1462_Test, TC1_CallsTarget) {
  ceres::internal::CompressedRowJacobianWriter target{};
  target.CreateEvaluatePreparers(nullptr);
}
