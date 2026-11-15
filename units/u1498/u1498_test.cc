// FILE: u1498_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(u1498_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.AddParameterBlock(nullptr, nullptr);
}
