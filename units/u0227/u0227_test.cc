// FILE: u0227_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CellInfoTest, DefaultConstructor_P1) {
  CellInfo cell_info;
  (void)cell_info;
}

}  // namespace internal
}  // namespace ceres
