// FILE: u0512_test.cc
#include "gtest/gtest.h"
#include "ceres/solver_utils.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0512, CallsTarget) {
  IsSolutionUsable({});
}
}  // namespace internal
}  // namespace ceres
