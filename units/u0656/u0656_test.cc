// FILE: u0656_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/iterative_refiner.h"
#include <memory>

// Path P1: START -> 1 -> END.
TEST(Unit_u0656, PathP1) {
  std::unique_ptr<ceres::internal::DenseCholesky> dense_cholesky;
  std::unique_ptr<ceres::internal::DenseIterativeRefiner> iterative_refiner;
  ceres::internal::RefinedDenseCholesky target(std::move(dense_cholesky), std::move(iterative_refiner));
}
