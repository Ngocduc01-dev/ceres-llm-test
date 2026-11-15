// FILE: u0720_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0720, CallsTarget) {
  Tail({}, 1);
}
}  // namespace internal
}  // namespace ceres
