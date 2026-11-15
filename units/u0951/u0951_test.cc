// FILE: u0951_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0951, TC1_CallsTarget) {
  Eigen::SparseMatrix<typename Solver::Scalar> lhs{};
  ceres::internal::EigenSparseCholeskyTemplate object{};
  object.Factorize(lhs, nullptr);
}
