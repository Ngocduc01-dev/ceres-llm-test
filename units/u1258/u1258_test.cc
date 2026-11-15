// FILE: u1258_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1258, TC1_CallsTarget) {
  )(const std::pair<T, T> p{};
  ceres::internal::pair_hash object{};
  object(p);
}
