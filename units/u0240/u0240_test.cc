// FILE: u0240_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CellConstructorTest, InitializesMembersP1) {
  Cell cell(3, 4);
  (void)cell;
}

}  // namespace internal
}  // namespace ceres
