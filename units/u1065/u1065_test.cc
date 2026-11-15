// FILE: u1065_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/problem_impl.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1065, TC1_CallsTarget) {
  int existing_block_size{};
  int new_block_size{};
  ceres::internal::(anonymous)::CheckForNoAliasing(nullptr, existing_block_size, nullptr, new_block_size);
}
