// FILE: u0719_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver.h"

// Path P1 calls Update(const Function & function, const Parameters & x).
TEST(Unitu0719, CallsTarget) {
  object.Update({}, {});
}

// Path P2 calls Update(const Function & function, const Parameters & x) on the alternate CFG path.
TEST(Unitu0719, CallsTargetAlternate) {
  object.Update({}, {});
}
