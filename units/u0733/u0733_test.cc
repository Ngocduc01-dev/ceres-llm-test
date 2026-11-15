// FILE: u0733_test.cc
#include "gtest/gtest.h"

namespace ceres {
// Path P1 calls MinimizerTypeToString(MinimizerType type).
TEST(Unitu0733, CallsTarget) {
  MinimizerTypeToString({});
}
}  // namespace ceres
