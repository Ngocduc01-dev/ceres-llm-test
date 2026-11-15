// FILE: u0699_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {
// Path P1 calls CellLessThan(const Cell & lhs, const Cell & rhs).
TEST(Unitu0699, CallsTarget) {
  CellLessThan({}, {});
}
}  // namespace internal
}  // namespace ceres
