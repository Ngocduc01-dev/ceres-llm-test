// FILE: u1345_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END
TEST(u1345_Test, TC1_CallsTarget) {
  ceres::internal::DenseSchurComplementSolver target{};
}
