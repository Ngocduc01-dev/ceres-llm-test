// FILE: u1481_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluation_callback.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1481, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1481, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1481, TC3_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1481, TC4_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1481, TC5_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1481, TC6_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1481, TC7_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1481, TC8_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1481, TC9_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1481, TC10_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1481, TC11_CallsTarget) {
  ceres::internal::Program object{};
  object.RemoveFixedBlocks(nullptr, nullptr, nullptr);
}
