// FILE: u0986_test.cc
#include "gtest/gtest.h"
#include "ceres/block_evaluate_preparer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0986, TC1_CallsTarget) {
  int max_derivatives_per_residual_block{};
  ceres::internal::BlockEvaluatePreparer object{};
  object.Init(nullptr, max_derivatives_per_residual_block);
}
