// FILE: u0734_test.cc
#include "gtest/gtest.h"

namespace ceres {
// Path P1 calls LineSearchTypeToString(LineSearchType type).
TEST(Unitu0734, CallsTarget) {
  LineSearchTypeToString({});
}
}  // namespace ceres
