// FILE: u1464_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_compressed_row_jacobian_writer.h"
#include "ceres/scratch_evaluate_preparer.h"

// P1: START -> 1 -> END
TEST(u1464_Test, TC1_CallsTarget) {
  ceres::internal::DynamicCompressedRowJacobianWriter target{};
  target.CreateEvaluatePreparers(nullptr);
}
