// FILE: u0549_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0549, CallsTarget) {
  CheckForDuplicates({});
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0549, CallsTargetAlternate) {
  CheckForDuplicates({});
}
}  // namespace internal
}  // namespace ceres
