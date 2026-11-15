// FILE: u0528_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

namespace ceres {
namespace internal {
// Path P1 calls InvokeOnSegment(int thread_id, std::tuple<int, int> range, F&& function).
TEST(Unitu0528, CallsTarget) {
  InvokeOnSegment(1, 1, {});
}
}  // namespace internal
}  // namespace ceres
