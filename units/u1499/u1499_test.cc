// FILE: u1499_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END
TEST(u1499_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.RemoveParameterBlock(nullptr);
}

// P2: START -> 1 -> END
TEST(u1499_Test, TC2_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.RemoveParameterBlock(nullptr);
}

// P3: START -> 1 -> END
TEST(u1499_Test, TC3_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.RemoveParameterBlock(nullptr);
}

// P4: START -> 1 -> END
TEST(u1499_Test, TC4_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.RemoveParameterBlock(nullptr);
}
