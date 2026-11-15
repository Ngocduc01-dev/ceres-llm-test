// FILE: u0965_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END
TEST(StopTest, TC1_CallsTarget) {
  ThreadPool object{};
  object.Stop();
}

