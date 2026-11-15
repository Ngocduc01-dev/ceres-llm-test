// FILE: u1464_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_compressed_row_jacobian_writer.h"
#include "ceres/scratch_evaluate_preparer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1464, TC1_CallsTarget) {
  int num_threads{};
  ceres::internal::DynamicCompressedRowJacobianWriter object{};
  object.CreateEvaluatePreparers(num_threads);
}
