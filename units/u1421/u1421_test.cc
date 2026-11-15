// FILE: u1421_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END
TEST(u1421_Test, TC1_CallsTarget) {
  ceres::internal::ContextImpl target{};
  target.EnsureMinimumThreads(nullptr);
}
