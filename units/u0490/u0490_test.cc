// FILE: u0490_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"
#include "ceres/thread_token_provider.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0490, PathP1) {
  int arg_0 = 1;
  ceres::internal::ThreadTokenProvider target(arg_0);
  target.ThreadTokenProvider(1);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0490, PathP2) {
  int arg_0 = 1;
  ceres::internal::ThreadTokenProvider target(arg_0);
  target.ThreadTokenProvider(1);
}
