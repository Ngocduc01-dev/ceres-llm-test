// FILE: u0730_test.cc
#include "gtest/gtest.h"

namespace ceres {
// Path P1 calls LinearSolverOrderingTypeToString(LinearSolverOrderingType type).
TEST(Unitu0730, CallsTarget) {
  LinearSolverOrderingTypeToString({});
}
}  // namespace ceres
