// FILE: u0353_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0353, PathP1) {
  uint64_t & arg_0{}
  uint64_t & arg_1{}
  uint64_t & arg_2{}
  ceres::internal::hash_mix(arg_0, arg_1, arg_2);
}
