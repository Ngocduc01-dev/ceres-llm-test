// FILE: u0545_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/memory.h"

namespace ceres {
namespace internal {
// Path P1 calls CopyRange(Allocator& alloc, Iterator destination, InputIterator first, InputIterator last).
TEST(Unitu0545, CallsTarget) {
  CopyRange({}, {}, {}, {});
}
}  // namespace internal
}  // namespace ceres
