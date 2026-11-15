// FILE: u0702_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0702, CallsTarget) {
  NumScalarEntries({});
}
}  // namespace internal
}  // namespace ceres
