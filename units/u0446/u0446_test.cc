// FILE: u0446_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/array_selector.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (CHECK_EQ(s, num_elements) đúng)
TEST(ArraySelectorConstructorTest, VectorSpecializationSizeMatches) {
  ArraySelector<int, 5, 2> selector(5);
}

}  // namespace internal
}  // namespace ceres
