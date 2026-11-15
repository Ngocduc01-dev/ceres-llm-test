// FILE: u0482_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 (đúng: manifold_ == nullptr) -> 2 -> END
TEST(ParameterBlockTangentSizeTest, TC1_NoManifold) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.TangentSize();
}

// P2: START -> 1 (sai: manifold_ != nullptr) -> 2 -> END
TEST(ParameterBlockTangentSizeTest, TC2_WithManifold) {
  double values[3] = {1.0, 2.0, 3.0};
  EuclideanManifold<3> manifold;
  ParameterBlock block(values, 3, 0, &manifold);
  block.TangentSize();
}

}  // namespace internal
}  // namespace ceres
