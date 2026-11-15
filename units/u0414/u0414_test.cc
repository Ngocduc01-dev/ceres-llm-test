// FILE: u0414_test.cc
#include <memory>
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"
TEST(Unit_u0414, Destruction) { std::unique_ptr<ceres::internal::SparseCholesky> target; }
