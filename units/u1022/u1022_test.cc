// FILE: u1022_test.cc
#include "gtest/gtest.h"
#include "ceres/scoped_thread_token.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1022, TC1_CallsTarget) {
  ceres::internal::ScopedThreadToken object{};
  object.~ScopedThreadToken();
}
