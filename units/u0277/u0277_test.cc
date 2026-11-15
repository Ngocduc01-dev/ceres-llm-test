// FILE: u0277_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/iterative_refiner.h"
#include <memory>

TEST(Unit_u0277, PathP1) {
  ceres::internal::RefinedDenseCholesky target(
      std::make_unique<ceres::internal::EigenDenseCholesky>(),
      std::make_unique<ceres::internal::DenseIterativeRefiner>(1));
}
