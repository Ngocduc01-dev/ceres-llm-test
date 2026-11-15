// FILE: u1326_test.cc
#include "gtest/gtest.h"
#include "ceres/casts.h"
#include "ceres/dynamic_compressed_row_finalizer.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1326, TC1_CallsTarget) {
  ceres::internal::DynamicCompressedRowJacobianFinalizer object{};
  object(nullptr);
}
