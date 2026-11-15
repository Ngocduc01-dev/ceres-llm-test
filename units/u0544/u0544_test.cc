// FILE: u0544_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/memory.h"

namespace ceres {
namespace internal {
// Path P1 calls ConstructRange(Allocator& alloc, Iterator first, Iterator last, const Args&args).
TEST(Unitu0544, CallsTarget) {
  ConstructRange({}, {}, {}, {});
}
}  // namespace internal
}  // namespace ceres
