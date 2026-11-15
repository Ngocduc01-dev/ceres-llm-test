// FILE: u0970_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END
TEST(ThreadMainLoopTest, TC1_CallsTarget) {
  ThreadPool object{};
  object.ThreadMainLoop();
}

// P2: START -> 1 -> END
TEST(ThreadMainLoopTest, TC2_CallsTarget) {
  ThreadPool object{};
  object.ThreadMainLoop();
}

