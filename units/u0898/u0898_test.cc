// FILE: u0898_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END
TEST(AddTaskTest, TC1_CallsTarget) {
  ThreadPool object{};
  std::function<void ()> & func a0{};
  object.AddTask(a0);
}

