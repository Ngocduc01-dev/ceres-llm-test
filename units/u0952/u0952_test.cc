// FILE: u0952_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END
TEST(ParallelForTest, TC1_CallsTarget) {
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  F&& function a4{};
  int a5 = 0;
  ceres::internal::ParallelFor(nullptr, a1, a2, a3, a4, a5);
}

// P2: START -> 1 -> END
TEST(ParallelForTest, TC2_CallsTarget) {
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  F&& function a4{};
  int a5 = 0;
  ceres::internal::ParallelFor(nullptr, a1, a2, a3, a4, a5);
}

// P3: START -> 1 -> END
TEST(ParallelForTest, TC3_CallsTarget) {
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  F&& function a4{};
  int a5 = 0;
  ceres::internal::ParallelFor(nullptr, a1, a2, a3, a4, a5);
}

