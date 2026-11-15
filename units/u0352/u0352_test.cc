// FILE: u0352_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0352, PathP1) { uint32_t a=1,b=2,c=3; ceres::internal::hash_mix(a,b,c); }
