// FILE: u0720_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {
// Path P1 calls Tail(const std::vector<Block> & blocks, int n).
TEST(Unitu0720, CallsTarget) {
  Tail({}, 1);
}
}  // namespace internal
}  // namespace ceres
