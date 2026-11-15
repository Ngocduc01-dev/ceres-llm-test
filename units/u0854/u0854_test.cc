// FILE: u0854_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/context_impl.h"
#include "ceres/eigen_vector_ops.h"

// P1: START -> 1 -> END
TEST(DotTest, TC1_CallsTarget) {
  VectorLikeX& x a0{};
  VectorLikeY& y a1{};
  int a3 = 0;
  ceres::internal::Dot(a0, a1, nullptr, a3);
}

