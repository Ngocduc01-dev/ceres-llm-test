// FILE: u1254_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_jacobi_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1254, TC1_CallsTarget) {
  ceres::internal::SchurJacobiPreconditioner object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr);
}
