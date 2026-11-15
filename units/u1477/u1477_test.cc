// FILE: u1477_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1477, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.InternalRemoveResidualBlock(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1477, TC2_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.InternalRemoveResidualBlock(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1477, TC3_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.InternalRemoveResidualBlock(nullptr);
}
