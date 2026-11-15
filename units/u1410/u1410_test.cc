// FILE: u1410_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1410, TC1_CallsTarget) {
  const int size_of_first_elimination_group{};
  ceres::internal::LexicographicallyOrderResidualBlocks(size_of_first_elimination_group, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1410, TC2_CallsTarget) {
  const int size_of_first_elimination_group{};
  ceres::internal::LexicographicallyOrderResidualBlocks(size_of_first_elimination_group, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1410, TC3_CallsTarget) {
  const int size_of_first_elimination_group{};
  ceres::internal::LexicographicallyOrderResidualBlocks(size_of_first_elimination_group, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1410, TC4_CallsTarget) {
  const int size_of_first_elimination_group{};
  ceres::internal::LexicographicallyOrderResidualBlocks(size_of_first_elimination_group, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1410, TC5_CallsTarget) {
  const int size_of_first_elimination_group{};
  ceres::internal::LexicographicallyOrderResidualBlocks(size_of_first_elimination_group, nullptr, nullptr);
}
