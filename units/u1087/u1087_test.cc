// FILE: u1087_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/iterative_refiner.h"

// P1: START -> 1 -> END
TEST(RefineTest, TC1_CallsTarget) {
  DenseIterativeRefiner object{};
  int a0 = 0;
  double a1[5] = {};
  double a2[5] = {};
  double a4[5] = {};
  object.Refine(a0, a1, a2, nullptr, a4);
}

// P2: START -> 1 -> END
TEST(RefineTest, TC2_CallsTarget) {
  DenseIterativeRefiner object{};
  int a0 = 0;
  double a1[5] = {};
  double a2[5] = {};
  double a4[5] = {};
  object.Refine(a0, a1, a2, nullptr, a4);
}

