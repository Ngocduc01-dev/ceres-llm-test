// FILE: u0737_test.cc
#include "gtest/gtest.h"

namespace ceres {
// Path P1 calls LoggingTypeToString(LoggingType type).
TEST(Unitu0737, CallsTarget) {
  LoggingTypeToString({});
}
}  // namespace ceres
