// FILE: u0852_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/eigen_vector_ops.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END
TEST(SetZeroTest, TC1_CallsTarget) {
  Vector & x a0{};
  int a2 = 0;
  ceres::internal::SetZero(a0, nullptr, a2);
}

