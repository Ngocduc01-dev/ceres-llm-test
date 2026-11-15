// FILE: u1222_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_pool.h"
#include "ceres/thread_pool.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1222, TC1_CallsTarget) {
  int requested_num_threads{};
  ceres::internal::(anonymous)::GetNumAllowedThreads(requested_num_threads);
}
