// FILE: u0875_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0875, TC1_CallsTarget) {
  int num_threads{};
  VectorType vector{};
  ceres::internal::ParallelSetZero(nullptr, num_threads, vector);
}
