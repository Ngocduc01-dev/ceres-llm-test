// FILE: u1271_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1271, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.IsBoundsConstrained();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1271, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.IsBoundsConstrained();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1271, TC3_CallsTarget) {
  ceres::internal::Program object{};
  object.IsBoundsConstrained();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1271, TC4_CallsTarget) {
  ceres::internal::Program object{};
  object.IsBoundsConstrained();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1271, TC5_CallsTarget) {
  ceres::internal::Program object{};
  object.IsBoundsConstrained();
}
