// FILE: u0242_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CompressedListConstructorTest, ConstructWithNumCells) {
  const int num_cells = 3;  // giá trị cố định trong khoảng [0, 5]
  CompressedList list(num_cells);
}

}  // namespace internal
}  // namespace ceres
