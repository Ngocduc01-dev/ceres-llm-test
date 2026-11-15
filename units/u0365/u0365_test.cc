// FILE: u0365_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockIndexTest, P1_ReturnIndex) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 2);
  block.index();
}

}  // namespace internal
}  // namespace ceres
