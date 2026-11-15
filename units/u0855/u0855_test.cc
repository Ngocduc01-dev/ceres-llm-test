// FILE: u0855_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/eigen_vector_ops.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0855, TC1_CallsTarget) {
  Vector from{};
  Vector to{};
  int num_threads{};
  ceres::internal::Copy(from, to, nullptr, num_threads);
}
