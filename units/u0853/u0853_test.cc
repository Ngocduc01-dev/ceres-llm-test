// FILE: u0853_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/eigen_vector_ops.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0853, TC1_CallsTarget) {
  double a{};
  Vector x{};
  double b{};
  Vector y{};
  Vector z{};
  int num_threads{};
  ceres::internal::Axpby(a, x, b, y, z, nullptr, num_threads);
}
