// FILE: u0784_test.cc
#include "gtest/gtest.h"
#include "ceres/visibility.h"
#include "ceres/graph.h"
#include "ceres/pair_hash.h"

// P1: START -> 1 -> END
TEST(CreateSchurComplementGraphTest, TC1_CallsTarget) {
  int a0 = 0;
  ceres::internal::CreateSchurComplementGraph(a0);
}

// P2: START -> 1 -> END
TEST(CreateSchurComplementGraphTest, TC2_CallsTarget) {
  int a0 = 0;
  ceres::internal::CreateSchurComplementGraph(a0);
}

// P3: START -> 1 -> END
TEST(CreateSchurComplementGraphTest, TC3_CallsTarget) {
  int a0 = 0;
  ceres::internal::CreateSchurComplementGraph(a0);
}

