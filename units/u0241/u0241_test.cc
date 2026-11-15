// FILE: u0241_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END
TEST(CompressedListTest, DefaultConstructor_P1) {
  CompressedList list;
  (void)list;
}

}  // namespace internal
}  // namespace ceres
