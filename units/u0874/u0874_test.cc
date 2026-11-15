// FILE: u0874_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0874, TC1_CallsTarget) {
  int num_threads{};
  int num_values{};
  ceres::internal::ParallelSetZero(nullptr, num_threads, nullptr, num_values);
}
