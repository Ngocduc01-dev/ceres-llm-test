// FILE: u0480_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 3 -> END (node 1: sai, upper_bounds_ == nullptr)
TEST(ParameterBlockUpperBoundTest, TC1_NoUpperBounds) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  double result = block.UpperBound(2);
  (void)result;
}

// P2: START -> 1 -> 2 -> 3 -> END (node 1: đúng, upper_bounds_ != nullptr)
TEST(ParameterBlockUpperBoundTest, TC2_WithUpperBounds) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetUpperBound(1, 4.5);
  double result = block.UpperBound(1);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
