// FILE: u1012_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

// P1: START -> 1 -> END
TEST(Hash64NumWithSeedTest, TC1_CallsTarget) {
  uint64_t a0{};
  uint64_t a1{};
  ceres::internal::Hash64NumWithSeed(a0, a1);
}

