// FILE: u1246_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"

// P1: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateTest, TC1_CallsTarget) {
  ImplicitSchurComplement object{};
  double a0[5] = {};
  double a1[5] = {};
  object.LeftMultiplyAndAccumulate(a0, a1);
}

