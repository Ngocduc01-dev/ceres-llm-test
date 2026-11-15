// FILE: u1209_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_invoke.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1209, TC1_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  int min_block_size{};
  ceres::internal::ParallelInvoke(nullptr, start, end, num_threads, function, min_block_size);
}
