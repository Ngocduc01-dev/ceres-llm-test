// FILE: u0727_test.cc
#include "gtest/gtest.h"
#include "ceres/inner_product_computer.h"

// Path P1 calls operator<(const ProductTerm & right) const.
TEST(Unitu0727, CallsTarget) {
  object.operator<({});
}

// Path P2 calls operator<(const ProductTerm & right) const on the alternate CFG path.
TEST(Unitu0727, CallsTargetAlternate) {
  object.operator<({});
}
