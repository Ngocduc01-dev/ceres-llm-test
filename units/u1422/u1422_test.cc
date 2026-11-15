// FILE: u1422_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_jacobian_writer.h"
#include "ceres/dense_sparse_matrix.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1422_Test, TC1_CallsTarget) {
  ceres::internal::DenseJacobianWriter target{};
  target.CreateJacobian();
}
