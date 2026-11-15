// FILE: u0039_test.cc
#include <memory>
#include <random>

#include "ceres/internal/fixed_array.h"
#include "gtest/gtest.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayCend, SinglePath) {
  std::mt19937 gen(12345);
  std::uniform_int_distribution<int> size_dist(1, 5);
  std::uniform_int_distribution<int> val_dist(0, 100);
  const size_t n = static_cast<size_t>(size_dist(gen));
  const int val = val_dist(gen);

  ceres::internal::FixedArray<int, 5> arr(n, val, std::allocator<int>());
  auto it = arr.cend();
  (void)it;
}
