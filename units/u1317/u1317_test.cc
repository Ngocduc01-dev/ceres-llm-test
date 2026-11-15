// FILE: u1317_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobian_writer.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"
#include "ceres/block_jacobian_writer.cc"

// P1: START -> 1 -> END
TEST(u1317_Test, TC1_CallsTarget) {
  BuildJacobianLayout(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1317_Test, TC2_CallsTarget) {
  BuildJacobianLayout(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1317_Test, TC3_CallsTarget) {
  BuildJacobianLayout(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1317_Test, TC4_CallsTarget) {
  BuildJacobianLayout(nullptr, nullptr, nullptr, nullptr);
}
