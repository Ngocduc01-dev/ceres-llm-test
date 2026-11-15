// FILE: u1011_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1011, TC1_CallsTarget) {
  uint32_t num{};
  uint32_t c{};
  ceres::internal::Hash32NumWithSeed(num, c);
}
