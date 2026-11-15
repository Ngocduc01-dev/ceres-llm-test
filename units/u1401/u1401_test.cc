// FILE: u1401_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block_ordering.h"
#include "ceres/graph_algorithms.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1401_Test, TC1_CallsTarget) {
  ComputeSchurOrdering(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1401_Test, TC2_CallsTarget) {
  ComputeSchurOrdering(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1401_Test, TC3_CallsTarget) {
  ComputeSchurOrdering(nullptr, nullptr);
}
