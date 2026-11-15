// FILE: u0540_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetUpperBound, P1_MaxBoundWithoutExistingBounds) {
  double state[3] = {0.1, 0.2, 0.3};
  ceres::internal::ParameterBlock block(state, 3, 0);
  block.SetUpperBound(2, std::numeric_limits<double>::max());
}
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetUpperBound, P2_AllocateBoundsThenSet) {
  double state[3] = {0.1, 0.2, 0.3};
  ceres::internal::ParameterBlock block(state, 3, 0);
  block.SetUpperBound(0, 5.0);
}
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetUpperBound, P3_BoundsAlreadyAllocated) {
  double state[3] = {0.1, 0.2, 0.3};
  ceres::internal::ParameterBlock block(state, 3, 0);
  // Chuẩn bị: cấp phát upper_bounds_ (lệnh gọi này không thuộc path P3).
  block.SetUpperBound(0, 3.5);
  // Lệnh gọi được kiểm thử theo P3.
  block.SetUpperBound(1, 7.25);
}
