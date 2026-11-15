// FILE: u0353_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0353, PathP1) { uint64_t a=1,b=2,c=3; ceres::internal::hash_mix(a,b,c); }
