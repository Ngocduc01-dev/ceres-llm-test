// FILE: u0549_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"

namespace ceres {
namespace internal {
// Path P1 calls CheckForDuplicates(std::vector<T> blocks).
TEST(Unitu0549, CallsTarget) {
  CheckForDuplicates({});
}

// Path P2 calls CheckForDuplicates(std::vector<T> blocks) on the alternate CFG path.
TEST(Unitu0549, CallsTargetAlternate) {
  CheckForDuplicates({});
}
}  // namespace internal
}  // namespace ceres
