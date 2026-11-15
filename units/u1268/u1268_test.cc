// FILE: u1268_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1268_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.SetParameterOffsetsAndIndex();
}

// P2: START -> 1 -> END
TEST(u1268_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.SetParameterOffsetsAndIndex();
}

// P3: START -> 1 -> END
TEST(u1268_Test, TC3_CallsTarget) {
  ceres::internal::Program target{};
  target.SetParameterOffsetsAndIndex();
}

// P4: START -> 1 -> END
TEST(u1268_Test, TC4_CallsTarget) {
  ceres::internal::Program target{};
  target.SetParameterOffsetsAndIndex();
}
