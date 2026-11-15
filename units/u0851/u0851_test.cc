// FILE: u0851_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/context_impl.h"
#include "ceres/eigen_vector_ops.h"

// P1: START -> 1 -> END
TEST(NormTest, TC1_CallsTarget) {
  Eigen::DenseBase<Derived>& x a0{};
  int a2 = 0;
  ceres::internal::Norm(a0, nullptr, a2);
}

