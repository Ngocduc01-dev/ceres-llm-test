// FILE: u0700_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {
// Path P1 calls SumSquaredSizes(const std::vector<Block> & blocks).
TEST(Unitu0700, CallsTarget) {
  SumSquaredSizes({});
}
}  // namespace internal
}  // namespace ceres
