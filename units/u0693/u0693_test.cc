// FILE: u0693_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"
#include "ceres/sparse_cholesky.h"

// Path P1 calls RefinedSparseCholesky(std::unique_ptr<SparseCholesky> sparse_cholesky, std::unique_ptr<SparseIterativeRefiner> iterative_refiner).
TEST(Unitu0693, CallsTarget) {
  object.RefinedSparseCholesky({}, {});
}
