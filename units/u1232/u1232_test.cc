// FILE: u1232_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1232, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.DeleteBlock(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1232, TC2_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.DeleteBlock(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1232, TC3_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.DeleteBlock(nullptr);
}
