// FILE: u0296_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0296, PathP1) {
  ceres::FirstOrderFunction* object = nullptr;
  object->~FirstOrderFunction();
}
