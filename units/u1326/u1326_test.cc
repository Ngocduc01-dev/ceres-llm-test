// FILE: u1326_test.cc
#include "gtest/gtest.h"
#include "ceres/casts.h"
#include "ceres/dynamic_compressed_row_finalizer.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1326_Test, TC1_CallsTarget) {
  ceres::internal::DynamicCompressedRowJacobianFinalizer target{};
  target.operator()(nullptr, nullptr);
}
