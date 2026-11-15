// FILE: u1303_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block_ordering.h"
#include "ceres/graph.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1303_Test, TC1_CallsTarget) {
  CreateHessianGraph(nullptr);
}

// P2: START -> 1 -> END
TEST(u1303_Test, TC2_CallsTarget) {
  CreateHessianGraph(nullptr);
}

// P3: START -> 1 -> END
TEST(u1303_Test, TC3_CallsTarget) {
  CreateHessianGraph(nullptr);
}

// P4: START -> 1 -> END
TEST(u1303_Test, TC4_CallsTarget) {
  CreateHessianGraph(nullptr);
}
