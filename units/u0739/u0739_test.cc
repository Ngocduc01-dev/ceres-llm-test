// FILE: u0739_test.cc
#include "gtest/gtest.h"

namespace ceres {
// Path P1 calls IsSchurType(LinearSolverType type).
TEST(Unitu0739, CallsTarget) {
  IsSchurType({});
}
}  // namespace ceres
