// FILE: u0945_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0945, TC1_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  int min_block_size{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, min_block_size);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0945, TC2_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  int min_block_size{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, min_block_size);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0945, TC3_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  int min_block_size{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, min_block_size);
}
