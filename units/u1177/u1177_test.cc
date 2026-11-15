// FILE: u1177_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(PlusTest, TC1_CallsTarget) {
  Program object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  int a4 = 0;
  object.Plus(a0, a1, a2, nullptr, a4);
}

