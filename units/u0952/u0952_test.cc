// FILE: u0952_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0952, TC1_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  std::vector<int> partitions{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, partitions);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0952, TC2_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  std::vector<int> partitions{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, partitions);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0952, TC3_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  std::vector<int> partitions{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, partitions);
}
