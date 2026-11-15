// FILE: u1259_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(u1259_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.IsParameterBlockConstant(nullptr);
}
