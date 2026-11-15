// FILE: u1254_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_jacobi_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1254_Test, TC1_CallsTarget) {
  ceres::internal::SchurJacobiPreconditioner target{};
  target.RightMultiplyAndAccumulate(nullptr, nullptr);
}
