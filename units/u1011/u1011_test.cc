// FILE: u1011_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

// P1: START -> 1 -> END
TEST(Hash32NumWithSeedTest, TC1_CallsTarget) {
  uint32_t a0{};
  uint32_t a1{};
  ceres::internal::Hash32NumWithSeed(a0, a1);
}

