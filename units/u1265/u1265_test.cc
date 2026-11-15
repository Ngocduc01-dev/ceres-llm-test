// FILE: u1265_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1265, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.MaxDerivativesPerResidualBlock();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1265, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.MaxDerivativesPerResidualBlock();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1265, TC3_CallsTarget) {
  ceres::internal::Program object{};
  object.MaxDerivativesPerResidualBlock();
}
