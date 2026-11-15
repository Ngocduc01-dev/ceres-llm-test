// FILE: u1347_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END
TEST(u1347_Test, TC1_CallsTarget) {
  ceres::internal::BlockRandomAccessDenseMatrix target{};
}

// P2: START -> 1 -> END
TEST(u1347_Test, TC2_CallsTarget) {
  ceres::internal::BlockRandomAccessDenseMatrix target{};
}
