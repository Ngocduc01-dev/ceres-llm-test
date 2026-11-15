// FILE: u0528_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0528, CallsTarget) {
  InvokeOnSegment(1, 1, {});
}
}  // namespace internal
}  // namespace ceres
