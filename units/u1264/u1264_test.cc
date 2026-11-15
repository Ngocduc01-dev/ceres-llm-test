// FILE: u1264_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END
TEST(u1264_Test, TC1_CallsTarget) {
  ceres::internal::ParameterBlock target{};
  target.SetState(nullptr);
}
