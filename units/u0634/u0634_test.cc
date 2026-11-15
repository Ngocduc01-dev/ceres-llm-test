// FILE: u0634_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

namespace ceres {
namespace internal {
// Path P1 calls operator>=(const FixedArray<T, N, A> & lhs, const FixedArray<T, N, A> & rhs).
TEST(Unitu0634, CallsTarget) {
  operator>=({}, {});
}
}  // namespace internal
}  // namespace ceres
