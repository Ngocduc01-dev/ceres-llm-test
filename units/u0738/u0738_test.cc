// FILE: u0738_test.cc
#include "gtest/gtest.h"

namespace ceres {
// Path P1 calls DumpFormatTypeToString(DumpFormatType type).
TEST(Unitu0738, CallsTarget) {
  DumpFormatTypeToString({});
}
}  // namespace ceres
