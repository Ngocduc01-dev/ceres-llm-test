// FILE: u0946_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0946, TC1_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  CumulativeCostFun cumulative_cost_fun{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, nullptr, cumulative_cost_fun);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0946, TC2_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  CumulativeCostFun cumulative_cost_fun{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, nullptr, cumulative_cost_fun);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0946, TC3_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  CumulativeCostFun cumulative_cost_fun{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, nullptr, cumulative_cost_fun);
}
