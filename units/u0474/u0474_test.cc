// FILE: u0474_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0474, PathP1) {
  const Collection& arg_0{}
  const typename Collection::value_type::first_type& arg_1{}
  const typename Collection::value_type::second_type& arg_2{}
  ceres::FindWithDefault<double>(arg_0, arg_1, arg_2);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0474, PathP2) {
  const Collection& arg_0{}
  const typename Collection::value_type::first_type& arg_1{}
  const typename Collection::value_type::second_type& arg_2{}
  ceres::FindWithDefault<double>(arg_0, arg_1, arg_2);
}
