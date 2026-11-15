// FILE: u0855_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/eigen_vector_ops.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END
TEST(CopyTest, TC1_CallsTarget) {
  Vector & from a0{};
  Vector & to a1{};
  int a3 = 0;
  ceres::internal::Copy(a0, a1, nullptr, a3);
}

