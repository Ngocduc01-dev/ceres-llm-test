// FILE: u1324_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/dense_normal_cholesky_solver.h"
#include "ceres/linear_solver.h"

// P1: START -> 1 -> END
TEST(u1324_Test, TC1_CallsTarget) {
  ceres::internal::DenseNormalCholeskySolver target{};
}
