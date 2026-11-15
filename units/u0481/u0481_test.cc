// FILE: u0481_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> 3 -> END (node 1: sai, lower_bounds_ == nullptr)
TEST(ParameterBlockLowerBoundTest, NoLowerBoundsAllocated) {
  double values[3] = {0.5, 1.5, -0.5};
  ParameterBlock block(values, 3, -1);
  double result = block.LowerBound(2);
  (void)result;
}

// Path P2: START -> 1 -> 2 -> 3 -> END (node 1: đúng, lower_bounds_ != nullptr)
TEST(ParameterBlockLowerBoundTest, LowerBoundsAllocated) {
  double values[4] = {0.1, 0.2, 0.3, 0.4};
  ParameterBlock block(values, 4, -1);
  block.SetLowerBound(1, -2.5);
  double result = block.LowerBound(1);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
