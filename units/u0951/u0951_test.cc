// FILE: u0951_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"

// P1: START -> 1 -> END
TEST(FactorizeTest, TC1_CallsTarget) {
  EigenSparseCholeskyTemplate object{};
  Eigen::SparseMatrix<typename Solver::Scalar> & lhs a0{};
  object.Factorize(a0, nullptr);
}

