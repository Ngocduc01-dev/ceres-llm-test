// FILE: u1311_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1311, TC1_CallsTarget) {
  int size_of_first_elimination_group{};
  ceres::internal::(anonymous)::MinParameterBlock(nullptr, size_of_first_elimination_group);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1311, TC2_CallsTarget) {
  int size_of_first_elimination_group{};
  ceres::internal::(anonymous)::MinParameterBlock(nullptr, size_of_first_elimination_group);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1311, TC3_CallsTarget) {
  int size_of_first_elimination_group{};
  ceres::internal::(anonymous)::MinParameterBlock(nullptr, size_of_first_elimination_group);
}
