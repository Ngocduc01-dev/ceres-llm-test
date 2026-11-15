// FILE: u0416_test.cc
#include <memory>
#include "gtest/gtest.h"
#include "ceres/sparse_normal_cholesky_solver.h"
TEST(Unit_u0416, Destruction) { std::unique_ptr<ceres::internal::SparseNormalCholeskySolver> target; }
