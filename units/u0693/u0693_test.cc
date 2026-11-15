// FILE: u0693_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"
#include "ceres/sparse_cholesky.h"
#include <memory>

// Path P1: START -> 1 -> END.
TEST(Unit_u0693, PathP1) {
  std::unique_ptr<ceres::internal::SparseCholesky> sparse_cholesky;
  std::unique_ptr<ceres::internal::SparseIterativeRefiner> iterative_refiner;
  ceres::internal::RefinedSparseCholesky target(std::move(sparse_cholesky), std::move(iterative_refiner));
}
