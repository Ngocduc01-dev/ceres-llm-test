// FILE: u1260_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1260_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.NumResiduals();
}

// P2: START -> 1 -> END
TEST(u1260_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.NumResiduals();
}
