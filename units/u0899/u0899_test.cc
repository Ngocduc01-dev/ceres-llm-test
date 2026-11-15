// FILE: u0899_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END
TEST(SizeTest, TC1_CallsTarget) {
  ThreadPool object{};
  object.Size();
}

