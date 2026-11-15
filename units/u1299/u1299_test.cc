// FILE: u1299_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/preconditioner.h"
#include "ceres/schur_jacobi_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1299_Test, TC1_CallsTarget) {
  ceres::internal::SchurJacobiPreconditioner target{};
}

// P2: START -> 1 -> END
TEST(u1299_Test, TC2_CallsTarget) {
  ceres::internal::SchurJacobiPreconditioner target{};
}
