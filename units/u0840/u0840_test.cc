// FILE: u0840_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0840, TC1_CallsTarget) {
  ceres::internal::ContextImpl object{};
  (void)object;
}
