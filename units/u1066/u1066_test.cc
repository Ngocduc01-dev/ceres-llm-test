// FILE: u1066_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END
TEST(UpdatePlusJacobianTest, TC1_CallsTarget) {
  ParameterBlock object{};
  object.UpdatePlusJacobian();
}

// P2: START -> 1 -> END
TEST(UpdatePlusJacobianTest, TC2_CallsTarget) {
  ParameterBlock object{};
  object.UpdatePlusJacobian();
}

// P3: START -> 1 -> END
TEST(UpdatePlusJacobianTest, TC3_CallsTarget) {
  ParameterBlock object{};
  object.UpdatePlusJacobian();
}

