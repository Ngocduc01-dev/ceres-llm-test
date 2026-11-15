// FILE: u1421_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1421, TC1_CallsTarget) {
  int num_threads{};
  ceres::internal::ContextImpl object{};
  object.EnsureMinimumThreads(num_threads);
}
