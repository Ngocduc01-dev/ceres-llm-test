// FILE: u0535_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// Path P1 calls AddElementToGroup(const T element, const int group).
TEST(Unitu0535, CallsTarget) {
  object.AddElementToGroup({}, 1);
}

// Path P2 calls AddElementToGroup(const T element, const int group) on the alternate CFG path.
TEST(Unitu0535, CallsTargetAlternate) {
  object.AddElementToGroup({}, 1);
}
