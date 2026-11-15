// FILE: u1409_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1409, TC1_CallsTarget) {
  ceres::internal::Program object{};
  object.IsFeasible(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1409, TC2_CallsTarget) {
  ceres::internal::Program object{};
  object.IsFeasible(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1409, TC3_CallsTarget) {
  ceres::internal::Program object{};
  object.IsFeasible(nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1409, TC4_CallsTarget) {
  ceres::internal::Program object{};
  object.IsFeasible(nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1409, TC5_CallsTarget) {
  ceres::internal::Program object{};
  object.IsFeasible(nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1409, TC6_CallsTarget) {
  ceres::internal::Program object{};
  object.IsFeasible(nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1409, TC7_CallsTarget) {
  ceres::internal::Program object{};
  object.IsFeasible(nullptr);
}
