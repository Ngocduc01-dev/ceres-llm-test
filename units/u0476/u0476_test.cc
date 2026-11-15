// FILE: u0476_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0476, PathP1) {
  const typename Collection::value_type::first_type& arg_1{}
  const typename Collection::value_type::second_type& arg_2{}
  ceres::InsertOrDie<double>(nullptr, arg_1, arg_2);
}
