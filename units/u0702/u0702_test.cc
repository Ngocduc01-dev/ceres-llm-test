// FILE: u0702_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {
// Path P1 calls NumScalarEntries(const std::vector<Block> & blocks).
TEST(Unitu0702, CallsTarget) {
  NumScalarEntries({});
}
}  // namespace internal
}  // namespace ceres
