// FILE: u1385_test.cc
#include "gtest/gtest.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1385, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.MaxScratchDoublesNeededForEvaluate();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1385, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.MaxScratchDoublesNeededForEvaluate();
}
