// FILE: u0238_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(BlockConstructorTest, SizeAndPositionInitializer) {
  Block block(3, 2);
  (void)block;
}

}  // namespace internal
}  // namespace ceres
