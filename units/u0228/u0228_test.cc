// FILE: u0228_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CellInfoConstructorTest, P1_ConstructWithValuesPointer) {
  double data[3] = {1.5, 2.5, 3.5};
  CellInfo cell_info(data);
  (void)cell_info;
}

}  // namespace internal
}  // namespace ceres
