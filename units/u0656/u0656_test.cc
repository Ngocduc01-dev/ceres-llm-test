// FILE: u0656_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/iterative_refiner.h"

// Path P1 calls RefinedDenseCholesky(std::unique_ptr<DenseCholesky> dense_cholesky, std::unique_ptr<DenseIterativeRefiner> iterative_refiner).
TEST(Unitu0656, CallsTarget) {
  object.RefinedDenseCholesky({}, {});
}
