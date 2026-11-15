// FILE: u1402_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block_ordering.h"
#include "ceres/ordered_groups.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1402_Test, TC1_CallsTarget) {
  ComputeRecursiveIndependentSetOrdering(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1402_Test, TC2_CallsTarget) {
  ComputeRecursiveIndependentSetOrdering(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1402_Test, TC3_CallsTarget) {
  ComputeRecursiveIndependentSetOrdering(nullptr, nullptr);
}
