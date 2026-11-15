// FILE: u1359_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/scratch_evaluate_preparer.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1359, TC1_CallsTarget) {
   int{};
  ceres::internal::ScratchEvaluatePreparer object{};
  object.Prepare(nullptr, int, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1359, TC2_CallsTarget) {
   int{};
  ceres::internal::ScratchEvaluatePreparer object{};
  object.Prepare(nullptr, int, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1359, TC3_CallsTarget) {
   int{};
  ceres::internal::ScratchEvaluatePreparer object{};
  object.Prepare(nullptr, int, nullptr, nullptr);
}
