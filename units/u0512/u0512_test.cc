// FILE: u0512_test.cc
#include "gtest/gtest.h"
#include "ceres/solver_utils.h"

namespace ceres {
namespace internal {
// Path P1 calls IsSolutionUsable(const SummaryType& summary).
TEST(Unitu0512, CallsTarget) {
  IsSolutionUsable({});
}
}  // namespace internal
}  // namespace ceres
