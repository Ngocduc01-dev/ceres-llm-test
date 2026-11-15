// FILE: u0478_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0478, PathP1) {
  int observed = 0;
  auto function = [&observed](int thread_id, int value) { observed = thread_id + value; };
  ceres::internal::InvokeWithThreadId(3, function, 4);
}
