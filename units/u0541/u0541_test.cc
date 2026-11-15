// FILE: u0541_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetLowerBoundTest, P1_EarlyReturnWhenNoBoundsAndLowest) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetLowerBound(1, -std::numeric_limits<double>::max());
}
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetLowerBoundTest, P2_AllocateBoundsThenAssign) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetLowerBound(2, 3.7);
}
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetLowerBoundTest, P3_AssignWhenBoundsAlreadyAllocated) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetLowerBound(0, -2.5);  // chuẩn bị: cấp phát lower_bounds_
  block.SetLowerBound(1, -std::numeric_limits<double>::max());
}

}  // namespace internal
}  // namespace ceres
