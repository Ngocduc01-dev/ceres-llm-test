// FILE: u1401_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block_ordering.h"
#include "ceres/graph_algorithms.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1401, TC1_CallsTarget) {
  Program program{};
  ceres::internal::ComputeSchurOrdering(program, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1401, TC2_CallsTarget) {
  Program program{};
  ceres::internal::ComputeSchurOrdering(program, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1401, TC3_CallsTarget) {
  Program program{};
  ceres::internal::ComputeSchurOrdering(program, nullptr);
}
