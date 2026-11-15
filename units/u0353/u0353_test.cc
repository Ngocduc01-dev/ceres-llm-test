// FILE: u0353_test.cc
#include <cstdint>
#include <random>

#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(HashMixTest, SinglePathNoBranch) {
  std::mt19937_64 rng(12345);
  uint64_t a = rng();
  uint64_t b = rng();
  uint64_t c = rng();
  hash_mix(a, b, c);
}

}  // namespace internal
}  // namespace ceres
