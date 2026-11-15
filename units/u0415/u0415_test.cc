// FILE: u0415_test.cc
#include <memory>
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"
TEST(Unit_u0415, Destruction) { std::unique_ptr<ceres::internal::RefinedSparseCholesky> target; }
