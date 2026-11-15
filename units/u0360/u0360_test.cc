// FILE: u0360_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END
TEST(ParameterBlockMutableUserStateTest, ReturnsUserState_P1) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 2);
  double* state = block.mutable_user_state();
  (void)state;
}

}  // namespace internal
}  // namespace ceres
