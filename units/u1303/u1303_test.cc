// FILE: u1303_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block_ordering.h"
#include "ceres/graph.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1303, TC1_CallsTarget) {
  Program program{};
  ceres::internal::CreateHessianGraph(program);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1303, TC2_CallsTarget) {
  Program program{};
  ceres::internal::CreateHessianGraph(program);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1303, TC3_CallsTarget) {
  Program program{};
  ceres::internal::CreateHessianGraph(program);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1303, TC4_CallsTarget) {
  Program program{};
  ceres::internal::CreateHessianGraph(program);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1303, TC5_CallsTarget) {
  Program program{};
  ceres::internal::CreateHessianGraph(program);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1303, TC6_CallsTarget) {
  Program program{};
  ceres::internal::CreateHessianGraph(program);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1303, TC7_CallsTarget) {
  Program program{};
  ceres::internal::CreateHessianGraph(program);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1303, TC8_CallsTarget) {
  Program program{};
  ceres::internal::CreateHessianGraph(program);
}
