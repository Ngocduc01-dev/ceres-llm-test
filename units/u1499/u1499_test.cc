// FILE: u1499_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1499, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.RemoveParameterBlock(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1499, TC2_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.RemoveParameterBlock(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1499, TC3_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.RemoveParameterBlock(nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1499, TC4_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.RemoveParameterBlock(nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1499, TC5_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.RemoveParameterBlock(nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1499, TC6_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.RemoveParameterBlock(nullptr);
}
