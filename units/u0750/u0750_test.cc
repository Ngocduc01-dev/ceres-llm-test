// FILE: u0750_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"

namespace ceres {
namespace internal {
// Path P1 calls operator<<(std::ostream & s, OrderingType type).
TEST(Unitu0750, CallsTarget) {
  operator<<({}, {});
}
}  // namespace internal
}  // namespace ceres
