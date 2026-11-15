// FILE: u0701_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {
// Path P1 calls operator==(const Block & left, const Block & right).
TEST(Unitu0701, CallsTarget) {
  operator==({}, {});
}
}  // namespace internal
}  // namespace ceres
