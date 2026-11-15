// FILE: u0854_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/context_impl.h"
#include "ceres/eigen_vector_ops.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0854, TC1_CallsTarget) {
  VectorLikeX x{};
  VectorLikeY y{};
  int num_threads{};
  ceres::internal::Dot(x, y, nullptr, num_threads);
}
