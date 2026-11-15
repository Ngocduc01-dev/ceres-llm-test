// FILE: u1012_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1012, TC1_CallsTarget) {
  uint64_t num{};
  uint64_t c{};
  ceres::internal::Hash64NumWithSeed(num, c);
}
