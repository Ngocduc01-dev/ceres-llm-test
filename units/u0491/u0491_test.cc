// FILE: u0491_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"
#include "ceres/thread_token_provider.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0491, PathP1) {
  ceres::internal::ThreadTokenProvider target;
  target.Acquire();
}
