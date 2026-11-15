// FILE: u0473_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0473, PathP1) {
  const Collection& arg_0{}
  const typename Collection::value_type::first_type& arg_1{}
  ceres::FindOrDie<double>(arg_0, arg_1);
}
