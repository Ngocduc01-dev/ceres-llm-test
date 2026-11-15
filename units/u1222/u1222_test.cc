// FILE: u1222_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_pool.h"
#include "ceres/thread_pool.cc"

// P1: START -> 1 -> END
TEST(GetNumAllowedThreadsTest, TC1_CallsTarget) {
  int a0 = 0;
  GetNumAllowedThreads(a0);
}

