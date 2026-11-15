// FILE: u0965_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0965, TC1_CallsTarget) {
  ceres::internal::ThreadPool object{};
  object.Stop();
}
