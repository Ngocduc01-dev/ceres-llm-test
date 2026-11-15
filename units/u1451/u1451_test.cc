// FILE: u1451_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(u1451_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.InternalSetManifold(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1451_Test, TC2_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.InternalSetManifold(nullptr, nullptr, nullptr);
}
