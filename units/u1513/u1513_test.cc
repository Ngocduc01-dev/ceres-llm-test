// FILE: u1513_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(u1513_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.AddParameterBlock(nullptr, nullptr, nullptr);
}
