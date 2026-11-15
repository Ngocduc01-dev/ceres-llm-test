// FILE: u1258_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

// P1: START -> 1 -> END
TEST(u1258_Test, TC1_CallsTarget) {
  ceres::internal::pair_hash target{};
  target.operator()(nullptr, nullptr);
}
