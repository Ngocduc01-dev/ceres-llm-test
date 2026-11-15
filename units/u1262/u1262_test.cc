// FILE: u1262_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1262, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.MaxResidualsPerResidualBlock();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1262, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.MaxResidualsPerResidualBlock();
}
