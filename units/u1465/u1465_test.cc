// FILE: u1465_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(u1465_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.InternalAddParameterBlock(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1465_Test, TC2_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.InternalAddParameterBlock(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1465_Test, TC3_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.InternalAddParameterBlock(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1465_Test, TC4_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.InternalAddParameterBlock(nullptr, nullptr);
}
