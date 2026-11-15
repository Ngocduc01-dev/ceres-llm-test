// FILE: u0352_test.cc
#include <cstdint>

#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(HashMixTest, SinglePathNoBranches) {
  uint32_t a = 2654435769u;
  uint32_t b = 1013904223u;
  uint32_t c = 1664525u;
  hash_mix(a, b, c);
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
