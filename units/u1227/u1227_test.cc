// FILE: u1227_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/context.h"
#include "ceres/casts.h"
#include "ceres/context_impl.h"
#include "ceres/problem_impl.cc"

// P1: START -> 1 -> END
TEST(InitializeContextTest, TC1_CallsTarget) {
  bool a2[5] = {};
  InitializeContext(nullptr, nullptr, a2);
}

// P2: START -> 1 -> END
TEST(InitializeContextTest, TC2_CallsTarget) {
  bool a2[5] = {};
  InitializeContext(nullptr, nullptr, a2);
}

