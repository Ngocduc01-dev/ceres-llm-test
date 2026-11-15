// FILE: u0523_test.cc
#include "gtest/gtest.h"
#include "ceres/casts.h"

namespace ceres {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0523, CallsTarget) {
  down_cast({});
}
}  // namespace ceres
