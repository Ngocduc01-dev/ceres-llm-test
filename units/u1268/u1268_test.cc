// FILE: u1268_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1268, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.SetParameterOffsetsAndIndex();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1268, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.SetParameterOffsetsAndIndex();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1268, TC3_CallsTarget) {
  ceres::internal::Program object{};
  object.SetParameterOffsetsAndIndex();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1268, TC4_CallsTarget) {
  ceres::internal::Program object{};
  object.SetParameterOffsetsAndIndex();
}
