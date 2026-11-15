// FILE: u0483_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// TC1 - P1: node 1: đúng (lower_bounds_ == nullptr) -> node 2 -> END
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockLowerBoundForParameter, NoLowerBoundsSet) {
  double x[3] = {0.5, 1.5, 2.5};
  ParameterBlock block(x, 3, 0);
  volatile double result = block.LowerBoundForParameter(1);
  (void)result;
}

// TC2 - P2: node 1: sai (lower_bounds_ != nullptr) -> node 3 -> END
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockLowerBoundForParameter, LowerBoundsSet) {
  double x[3] = {0.5, 1.5, 2.5};
  ParameterBlock block(x, 3, 0);
  block.SetLowerBound(1, -2.5);
  volatile double result = block.LowerBoundForParameter(1);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
