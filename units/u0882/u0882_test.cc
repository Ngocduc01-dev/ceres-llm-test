// FILE: u0882_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(mutable_implTest, TC1_CallsTarget) {
  Problem object{};
  object.mutable_impl();
}

