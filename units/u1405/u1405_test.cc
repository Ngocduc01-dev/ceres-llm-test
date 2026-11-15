// FILE: u1405_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block_ordering.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END
TEST(u1405_Test, TC1_CallsTarget) {
  ComputeStableSchurOrdering(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1405_Test, TC2_CallsTarget) {
  ComputeStableSchurOrdering(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1405_Test, TC3_CallsTarget) {
  ComputeStableSchurOrdering(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1405_Test, TC4_CallsTarget) {
  ComputeStableSchurOrdering(nullptr, nullptr);
}
