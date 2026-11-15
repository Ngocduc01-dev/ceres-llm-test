// FILE: u1209_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_invoke.h"

// P1: START -> 1 -> END
TEST(ParallelInvokeTest, TC1_CallsTarget) {
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  F&& function a4{};
  int a5 = 0;
  ceres::internal::ParallelInvoke(nullptr, a1, a2, a3, a4, a5);
}

