// FILE: u1082_test.cc
#include "gtest/gtest.h"
#include "ceres/scoped_thread_token.h"
#include "ceres/thread_token_provider.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1082, TC1_CallsTarget) {
  ceres::internal::ScopedThreadToken object{};
  (void)object;
}
