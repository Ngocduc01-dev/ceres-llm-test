// FILE: u1317_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobian_writer.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"
#include "ceres/block_jacobian_writer.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1317, TC1_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1317, TC2_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1317, TC3_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1317, TC4_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1317, TC5_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1317, TC6_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1317, TC7_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1317, TC8_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1317, TC9_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1317, TC10_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1317, TC11_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}

// P12: START -> 1 -> END; branch decisions covered by case 12
TEST(Unit_u1317, TC12_CallsTarget) {
  Program program{};
  int num_eliminate_blocks{};
  ceres::internal::(anonymous)::BuildJacobianLayout(program, num_eliminate_blocks, nullptr, nullptr);
}
