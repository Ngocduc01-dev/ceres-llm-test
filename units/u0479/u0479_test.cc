// FILE: u0479_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(ParameterBlockGetStateTest, P1_XDifferentFromState) {
  double user_state[3] = {1.0, 2.0, 3.0};
  double x[3] = {0.0, 0.0, 0.0};
  ParameterBlock block(user_state, 3, 0);
  block.GetState(x);
}

// Path P2: START -> 1 -> END (node 1: sai)
TEST(ParameterBlockGetStateTest, P2_XEqualsState) {
  double user_state[4] = {5.0, 6.0, 7.0, 8.0};
  ParameterBlock block(user_state, 4, 0);
  block.GetState(user_state);
}

}  // namespace internal
}  // namespace ceres
