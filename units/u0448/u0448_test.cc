// FILE: u0448_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

namespace ceres {
namespace internal {

using IntFixedArray = FixedArray<int, 20>;

// P1: START -> 1 -> 2 (sai) -> END ; k = 0
TEST(FixedArrayDestructorTest, ZeroIterations) {
  {
    IntFixedArray arr(0, IntFixedArray::allocator_type());
  }
}

// P2: node 2: đúng, sai ; k = 1
TEST(FixedArrayDestructorTest, OneIteration) {
  {
    IntFixedArray arr(1, IntFixedArray::allocator_type());
  }
}

// P3: node 2: đúng, đúng, sai ; k = 2
TEST(FixedArrayDestructorTest, TwoIterations) {
  {
    IntFixedArray arr(2, IntFixedArray::allocator_type());
  }
}

// P4: node 2: đúng x3, sai ; k = 3 (giá trị ở giữa)
TEST(FixedArrayDestructorTest, MiddleIterations) {
  {
    IntFixedArray arr(3, IntFixedArray::allocator_type());
  }
}

// P5: node 2: đúng x4, sai ; k = 4 (n-1)
TEST(FixedArrayDestructorTest, NMinusOneIterations) {
  {
    IntFixedArray arr(4, IntFixedArray::allocator_type());
  }
}

// P6: node 2: đúng x5, sai ; k = 5 (n)
TEST(FixedArrayDestructorTest, NIterations) {
  {
    IntFixedArray arr(5, IntFixedArray::allocator_type());
  }
}

}  // namespace internal
}  // namespace ceres
