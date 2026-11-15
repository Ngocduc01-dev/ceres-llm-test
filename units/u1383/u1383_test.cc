// FILE: u1383_test.cc
#include "gtest/gtest.h"
#include "ceres/block_evaluate_preparer.h"
#include "ceres/block_jacobian_writer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1383, TC1_CallsTarget) {
  unsigned int num_threads{};
  ceres::internal::BlockJacobianWriter object{};
  object.CreateEvaluatePreparers(num_threads);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1383, TC2_CallsTarget) {
  unsigned int num_threads{};
  ceres::internal::BlockJacobianWriter object{};
  object.CreateEvaluatePreparers(num_threads);
}
