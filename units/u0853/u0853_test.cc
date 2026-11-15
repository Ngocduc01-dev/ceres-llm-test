// FILE: u0853_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/eigen_vector_ops.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END
TEST(AxpbyTest, TC1_CallsTarget) {
  double a0 = 0.0;
  Vector & x a1{};
  double a2 = 0.0;
  Vector & y a3{};
  Vector & z a4{};
  int a6 = 0;
  ceres::internal::Axpby(a0, a1, a2, a3, a4, nullptr, a6);
}

