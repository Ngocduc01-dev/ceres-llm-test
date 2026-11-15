// FILE: u0445_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/array_selector.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (CHECK_EQ đúng, s == num_elements == 3)
TEST(ArraySelectorConstructorTest, P1_SizeEqualsNumElements) {
  ArraySelector<int, 3, 20> selector(3);
  (void)selector;
}

}  // namespace internal
}  // namespace ceres
